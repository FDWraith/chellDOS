#include <stdio.h>
#include <stdlib.h>

#include "parse.h"

int main(){
  char s[100] = "ls -l; echo hello\n";
  parseInput( s);

}
