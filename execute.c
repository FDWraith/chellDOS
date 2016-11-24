#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

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
        //printf("Carrot Success\n");
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
    if( strcmp( cmd[i], target ) == 0 ){
      if( strcmp( target, "|") == 0){
        //Specia; case #1
      }else if( strcmp( target, "<" ) == 0){
        //Special case #2 
      }else{
        int fd = openSpecialChar( target, cmd[i+1]);
        int fd2 = dup(fd);//Store STDOut
        dup2(fd, 1);
        int status;

        int j = 0;
          char * * cmdTemp = (char * *)malloc(sizeof( char * *));
          for(; j < i; j++){
            cmdTemp[j] = cmd[j];
            j++;
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
  if( strcmp( target, ">") == 0){
    int fd = open( path, O_CREAT | O_WRONLY, 666);
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