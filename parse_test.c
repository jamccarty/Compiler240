#include <stdio.h>
#include <stdlib.h>
#include "ParseFunctionHeader.h"

int main(int argc, char** argv) {
  char **param_array;
  int i = 0;

  if (argc < 2) {
    printf("Error: A filename must be entered.\n");
    exit(1);
  } else if (argc > 2) {
    printf("Error: Only one filename must be entered.\n");
    exit(1);
  }

  param_array = parse_function_header(argv[1]);
  
  if (param_array[i][0] != '\0') {
    printf("All function parameter names: \n");
    
    while (param_array[i][0] != '\0') {
      printf("%s\n", param_array[i]);
      i++; 
    }
  } else {
    printf("There are no function parameter names.\n");
  }

  for (int j = 0; j < 100; j++) {
    free(param_array[j]);
    param_array[j] = NULL;
  }

  free(param_array);
  param_array = NULL;

  return 0;
}
