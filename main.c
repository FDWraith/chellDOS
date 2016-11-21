#include <stdio.h>
#include <stdlib.h>

#include "parse.h"
#include "execute.h"

int main(){
  char s[1000];
  printf(">");
  while( fgets(s, sizeof(s), stdin) ){
    char * * * cmdList = parseInput( s );
    executeList( cmdList );
    printf(">");
  }
}
