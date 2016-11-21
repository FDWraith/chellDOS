#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * * parseLine( char * string);


char * * * parseInput( char * string ){

  //printf(" Does it get Here? \n");
  
  //Getting rid of newlines
  int j = 0;
  for(; j < strlen(string); j++ ){
    if( strcmp( &string[j], "\n" ) == 0 ){
      string[j] = 0;
      j--;
    }
  }

  char * * * cmdList = (char * * *)malloc( sizeof( char *) * 100 * 100);
  char * currentString = string;
  int i = 0;

  //printf(" Got Here! \n" );
  
  while( currentString ){
    
    char * copyString = strsep(&currentString, ";");

    printf(" Phase 1 \n");
    printf(" copyString Value: [%s] \n", copyString);
    
    cmdList[i] = parseLine( copyString );
    i++;
  }
  cmdList[i] = 0;

  //Testing cmdList
  
  printf("Testing cmdList\n");
  int l = 0;
  //printf("[%s]\n", cmdList[0][2]);

  while( cmdList[l] != NULL){
    j = 0;
    //printf("Pointer [%p]\n", cmdList[l]);
    while( cmdList[l][j] != NULL ){
      printf("%s ", cmdList[l][j]);
      j++;
    }
    l++;
    printf("\n");
  }

  printf("Testing Successful\n");
  return cmdList;

}

char * * parseLine( char * string ){

  //Removing newLine
  int j = 0;
  for(; j < strlen(string); j++ ){
    if( strcmp( &string[j], "\n" ) == 0 ){
      string[j] = 0;
      j--;
    }
  }

  char * copyString = string;
  int k = 0;
  char * * cmd = (char * *)malloc(sizeof(char *) * 100);
  
  while ( copyString ){
    char * p = strsep( &copyString, " ");
    if( strcmp( p, "" ) != 0 ){
      cmd[k] = p;
      printf("cmdArg: [%s]\n", cmd[k] );
      k++;
    }
  }
  cmd[k] = 0;

  return cmd;
}
