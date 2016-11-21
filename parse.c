#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char * * parseInput( char * string ){

  printf(" Does it get Here? \n");
  
  //Getting rid of newlines
  int j = 0;
  for(; j < strlen(string); j++ ){
    if( strcmp( &string[j], "\n" ) == 0 ){
      string[j] = 0;
      j--;
    }
  }

  char * * cmdList[100];
  char * currentString = string;
  int i =0;

  printf(" Got Here! \n" );
  
  while( currentString ){
    char * cmd[100];
    char * copyString = strsep(&currentString, ";");
    int k = 0;

    printf(" Phase 1 \n");
    printf(" copyString Value: [%s] \n", copyString);
    
    while ( copyString ){
      char * p = strsep( &copyString, " ");
      if( strcmp( p, "" ) != 0 ){
        cmd[k] = p;
        printf("cmdArg: [%s]\n", cmd[k] );
        k++;
      }
    }
    cmd[k] = 0;
    cmdList[i] = cmd;
  }

  //Testing cmdList
  /*
  printf("Testing cmdList\n");
  int l = 0;
  while( cmdList[l] ){
    j = 0;
    while( cmdList[i][j] ){
      printf("%s ", cmdList[i][j]);
    }
    printf("\n");
  }
  */
  
}
