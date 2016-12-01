#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>


int executeSpecialChar( char * * cmd, char * target );
int openSpecialChar(char * target, char * path);

//Executes one line of command.
//Takes an array of strings, which is the parsed command from stdin.
//Returns pid of child.
int executeLine( char * * cmd){
  if( strcmp(cmd[0], "exit") == 0){
    exit(0);
  }else if( strcmp( cmd[0], "cd" ) == 0){
    chdir( cmd[1] );
  }else{    
    int f = fork();
    int status;
    
    if( f == 0){

      if ( executeSpecialChar( cmd, ">") ){
        exit(0);        
      }else if( executeSpecialChar( cmd, ">>" ) ){
        exit(0);
      }else if( executeSpecialChar( cmd, "2>" ) ){
        exit(0);
      }else if( executeSpecialChar( cmd, "2>>" ) ){
        exit(0);
      }else if( executeSpecialChar( cmd, "<" ) ){
        exit(0);
      }else if( executeSpecialChar( cmd, "|" ) ){
        exit(0);
      }else{
        execvp( cmd[0], cmd);
      }
      
      /*
      if( ){
    
      }else if( strcmp( cmd[1], ">>" ) == 0){
          
      }else if( strcmp( cmd[1], "2>" ) == 0){
        
      }else if( strcmp( cmd[1], "&>" ) == 0){
        
      }else if( strcmp( cmd[1], "2>>" ) == 0){
        
      }else if( strcmp( cmd[1], "<" ) == 0){
          
      }else if( strcmp( cmd[1], "|") == 0){
        
      }else{
        execvp(cmd[0], cmd);
      }
    */
    }else{
      return wait(&status);
    }
  }
}

int executeSpecialChar( char * * cmd, char * target){
  int i = 0;
  while( cmd[i] ){
    //printf("Cmd[%d]: %s\n", i, cmd[i]);
    if( strcmp( cmd[i], target ) == 0 ){
      int fd, fd2;
      if( strcmp( target, "|") == 0){
        //Specia; case #1
        //printf("Special Case #1\n");

        int j = 0;
        char * * cmdBefore = (char * *)malloc(sizeof( char * *));
        char * * cmdAfter = (char * *)malloc(sizeof( char * *));
        for(; j < i; j++){
          cmdBefore[j] = cmd[j];
          //printf("Current:[%s]", cmdBefore[j]);
        }
        cmdBefore[j] = 0;
        
        //cmdBefore[j+1] = "tempFile";
        //cmdBefore[j+2] = 0;

        j = i + 1;
        while( cmd[j] ){
          cmdAfter[j - i - 1] = cmd[j];
          //printf("Current:[%s]\n", cmdAfter[j -i -1]);
          j++;
        }
        cmdAfter[j] = 0;

        //cmdAfter[j+1] = "tempFile";
        //cmdAfter[j+2] = 0;

        printf("Flag 1\n");
        int fds[2];
        pipe(fds);

        printf("Flag 1.5\n");
        
        fd2 = dup(1);
        dup2(fds[1], 1);
        int status;

        dup2(1, fd2);
        printf("Flag Status: Active\n");
        dup2( fds[1], 1);
          
        int f = fork();
        if (f == 0) {
          close(fds[0]);
          execvp(cmdBefore[0], cmdBefore);
        }
        else {         
          wait(&status);
          dup2(1, fd2);
          //printf("%s", s);
        }

        printf("Flag 2\n");
        
        fd2 = dup(0);
        dup2(fds[0], 0);
        int f2 = fork();
        if (f2 == 0) {
          close(fds[1]);
          execvp(cmdAfter[0], cmdAfter);
        }
        else {
          wait(&status);
          dup2(0, fd2);
        }
        printf("Flag 3\n");
        return 1;
        
      }else{
        if( strcmp( target, "<" ) == 0){
          fd = openSpecialChar( target, cmd[i+1]);
          fd2 = dup(fd);
          dup2(fd, 0);
        }else if( strcmp( target, "2>") == 0 || strcmp( target, "2>>") == 0){
          fd = openSpecialChar( target, cmd[i+1]);
          fd2 = dup(fd);
          dup2(fd, 2);
        }else{
          fd = openSpecialChar( target, cmd[i+1]);
          fd2 = dup(fd);
          dup2(fd, 1);
        }
        int status;
        
        int j = 0;
        char * * cmdTemp = (char * *)malloc(sizeof( char * *));
        for(; j < i; j++){
          cmdTemp[j] = cmd[j];
        }
        
        int f = fork();
        if( f == 0 ){
          
          execvp( cmdTemp[0], cmdTemp);
          
        }else{
          wait(&status);
          free(cmdTemp);
          close(fd2);
          return 1;
        }
      }
      
    }
    i++;
  }
  return 0;
}

int openSpecialChar( char  * target , char * path){
  umask(0);
  if( strcmp( target, ">") == 0 || strcmp( target, "2>") == 0){
    int fd = open( path, O_CREAT | O_WRONLY | O_TRUNC, 666);
    return fd;
  }else if( strcmp( target, ">>" ) == 0 || strcmp( target, "2>>" ) == 0){
    int fd = open( path, O_CREAT | O_APPEND, 666);
    return fd;
  }else if( strcmp( target, "<" ) == 0){
    int fd = open( path, O_CREAT | O_RDONLY, 444);
    return fd;
  }
  
  
  //int fd = open(, O_CREAT | O_WRONLY, 666);
}

void executeList( char * * * cmdList){
  int j = 0;
  while( cmdList[j] ){
    executeLine( cmdList[j] );
    j++;
  }
}
