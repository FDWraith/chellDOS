#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

//Executes one line of command.
//Takes an array of strings, which is the parsed command from stdin.
//Returns pid of child.
int executeLine( char * * cmd){
  int f = fork();
  int status;
  if( f == 0){
    execvp(cmd[0], cmd);
  }else{
    return wait(&status);
  }
}

void executeList( char * * * cmdList){
  int j = 0;
  while( cmdList[j] ){
    executeLine( cmdList[j] );
    j++;
  }
}
