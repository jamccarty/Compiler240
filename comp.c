#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_function_header(char *first_line) {
  char *space = " ";
  char *token = strtok(line, space);
  
  if (strcmp(token, "int") != 0) {
    printf("Error: The return type of the function is undeclared.\n");
    exit(1);
  }
  
  token = strtok(NULL, space);
  
  if (strcmp(token, "(") == 0) {
    printf("Error: The function has no name!\n");
    exit(1);
  }
  
  token = strtok(NULL, space);
  
  if (strcmp(token, "(") == 0) {
    while (token != NULL) {
      token = strtok(line, space);
    
      if (strcmp(token, "int") != 0) {
        printf("Error: The return type of the function is undeclared.\n");
        exit(1);
      } else {
        token = strtok(line, space);
        if ((strcmp(token, ",") != 0) && (strcmp(token, "int") != 0)) {
          
        }
      }
    }
  }
}

int main() {
  char *whitespace = " \t\f\r\v\n";
}
