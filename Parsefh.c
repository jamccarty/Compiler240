#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ParseFunctionHeader.h"

char** parse_function_header(const char* filename) {
  FILE *file;
  char *whitespace = " \t\f\r\v\n";
  char *token;
  char **array;
  char *line = NULL;
  int j = 0;

  line = malloc(sizeof(char) * 150);

  if (line == NULL) {
    printf("Error: malloc failed!\n");
    exit(1);
  }

  array = malloc(sizeof(char*) * 100);

  for (int i = 0; i < 100; i++) {
    array[i] = malloc(sizeof(char) * 150);
    memset(array[i], (int)'\0', 149);
  }

  if (array == NULL) {
    return NULL;
  }

  file = fopen(filename, "r");

  if (file == NULL) {
    printf("Error with file.\n");
    exit(1);
  }

  fgets(line, 100, file);

  token = strtok(line, whitespace);
  if (strcmp(token, "int") != 0) {
    printf("Error: Need to declare return type for function!\n");
    exit(1);
  }
  
  token = strtok(NULL, whitespace);
  if (strcmp(token, "(") == 0) {
    printf("Error: Missing a function name.\n");
    exit(1);
  }

  token = strtok(NULL, whitespace);
  if (strcmp(token, "(") != 0) {
    printf("Error: Missing open parentheses for function's parameters.\n");
    exit(1);
  }

  token = strtok(NULL, whitespace);
  while (token != NULL) {
    if (strcmp(token, ")") == 0) {
      break;
    } else if (strcmp(token, "int") != 0) {
      printf("Error: Missing parameter's variable type declaration.\n");
      exit(1);
    } else {
      token = strtok(NULL, whitespace);
      
      if ((strcmp(token, "int") != 0) && (strcmp(token, ")") != 0) &&
        (strcmp(token, ",") != 0)) {
        strcpy(array[j], token);
        j++;
      } else {
        printf("Error: No variable name declared.\n");
        exit(1);
      }
    }

    token = strtok(NULL, whitespace);

    if (strcmp(token, ")") == 0) {
      break;
    } else if (strcmp(token, ",") != 0) {
      printf("Error: Invalid parameter.\n");
      exit(1);
    }

    token = strtok(NULL, whitespace);
  }

  free(line);
  line = NULL;
  
  fclose(file);

  return array;
}

