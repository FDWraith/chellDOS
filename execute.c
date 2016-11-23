#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>

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
    }else{
      return wait(&status);
    }
  }
}

void executeSpecialChar( char * * cmd, char * target){
  int i = 0;
  while( cmd[i] ){    
    if( strcmp( cmd[i], target ) == 0){
      int fd2 = dup(1);
      dup2(1, fd);
      int f2 = fork();
      if( f2 == 0){
        char * * cmdTemp1 = (char * *)malloc(sizeof(char * *));
        int j = 0;
        for(; j < i; j++){
          cmdTemp1[j] = cmd[j];
        }
        execvp(cmdTemp1[0], cmdTemp1);
      }else{
        
      }
    }

  }
}

int openSpecialChar( char  * target , char * path){
  if( strcmp( target, ">") == 0){
    int fd = open( path, OCREAT | O_WRONLY, 666);
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
