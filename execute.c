#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int executeSpecialChar(char * * cmd, char * target );
int openSpecialChar(char * target, char * path);

// Executes a single command.
// Takes an array of strings, cmd (parsed command from stdin)
// Returns pid of child.
int executeLine(char * * cmd){
  if (strcmp(cmd[0], "exit") == 0) {
    exit(0);
  }
  else if (strcmp(cmd[0], "cd") == 0) {
    chdir(cmd[1]);
  }
  else{    
    int f = fork();
    int status;
    
    if( f == 0){
      if (executeSpecialChar(cmd, ">")) {
        exit(0);        
      }
      else if (executeSpecialChar(cmd, ">>")) {
        exit(0);
      }
      else if (executeSpecialChar(cmd, "2>")) {
        exit(0);
      }
      else if (executeSpecialChar(cmd, "2>>")) {
        exit(0);
      }
      else if (executeSpecialChar(cmd, "<")) {
        exit(0);
      }
      else if (executeSpecialChar(cmd, "|")) {
        exit(0);
      }
      else {
        execvp(cmd[0], cmd);
      }
    }
    else {
      return wait(&status);
    }
  }
}

// Helper function to execute special commands.
/* Takes an array of strings, cmd (the parsed command) and a string, target, that
   contains a special command symbol (i.e. >, <, |, etc.) */
// Returns 1 if the special command was successfully executed, 0 otherwise.
int executeSpecialChar(char * * cmd, char * target){
  int i = 0;
  while (cmd[i]) {
    if (strcmp(cmd[i], target) == 0) {
      int fd, fd2;
      
      // piping
      if (strcmp(target, "|") == 0) {
        int j = 0;
        char * * cmdBefore = (char * *)malloc(sizeof( char * *));
        char * * cmdAfter = (char * *)malloc(sizeof( char * *));
        
        for(; j < i; j++){
          cmdBefore[j] = cmd[j];
        }
        cmdBefore[j] = 0;  // null end
        
        j = i + 1;
        while(cmd[j]){
          cmdAfter[j - i - 1] = cmd[j];
          j++;
        }
        cmdAfter[j] = 0;  // null end

        int fds[2];
        pipe(fds);

        fd2 = dup(1);
        int status;          
        int f = fork();
        if (f == 0) {
          dup2(fds[1], 1);
          execvp(cmdBefore[0], cmdBefore);
        }
        else {         
          wait(&status);
          dup2(1, fd2);
          close(fds[1]);
        }

        int status2;
        int f2 = fork();
        fd2 = dup(0);
        if (f2 == 0) {
          dup2(fds[0], 0);
          execvp(cmdAfter[0], cmdAfter);
        }
        else {
          wait(&status2);
          dup2(0, fd2);
          close( fds[0]);
        }
        return 1;
      }
      
      else {
        // redirecting stdin
        if( strcmp( target, "<" ) == 0) {
          fd = openSpecialChar( target, cmd[i+1]);
          fd2 = dup(fd);
          dup2(fd, 0);
        }
        // redirecting stderr
        else if( strcmp( target, "2>") == 0 || strcmp( target, "2>>") == 0) {
          fd = openSpecialChar( target, cmd[i+1]);
          fd2 = dup(fd);
          dup2(fd, 2);
        }
        // redirecting stdout
        else {
          fd = openSpecialChar(target, cmd[i+1]);
          fd2 = dup(fd);
          dup2(fd, 1);
        }
        
        int status;
        int j = 0;
        char * * cmdTemp = (char * *) malloc(sizeof( char * *));
        for(; j < i; j++){
          cmdTemp[j] = cmd[j];
        }
        
        int f = fork();
        if(f == 0){
          execvp(cmdTemp[0], cmdTemp);
        }
        else{
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

// Helper function to open files for redirection.
/* Takes a string, target, that contains a special command symbol and 
   another string, path, that contains the path to the file to be opened. */
// Returns the file descriptor of the opened file.
int openSpecialChar (char * target , char * path) {
  umask(0);
  if( strcmp( target, ">") == 0 || strcmp( target, "2>") == 0){
    int fd = open( path, O_CREAT | O_WRONLY | O_TRUNC, 666);
    return fd;
  }
  else if( strcmp( target, ">>" ) == 0 || strcmp( target, "2>>" ) == 0){
    int fd = open( path, O_CREAT | O_WRONLY | O_APPEND, 666);
    return fd;
  }
  else if( strcmp( target, "<" ) == 0){
    int fd = open( path, O_CREAT | O_RDONLY, 444);
    return fd;
  }
}

// Executes multiple commands on a single line
// Takes an array of an array of strings (an array of parsed commands)
// Void return type
void executeList (char * * * cmdList){
  int j = 0;
  while( cmdList[j] ){
    executeLine(cmdList[j]);
    j++;
  }
}
