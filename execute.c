#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>

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
      execvp(cmd[0], cmd);
    }else{
      return wait(&status);
    }
  }
}

void executeList( char * * * cmdList){
  int j = 0;
  while( cmdList[j] ){
    executeLine( cmdList[j] );
    j++;
  }
}
