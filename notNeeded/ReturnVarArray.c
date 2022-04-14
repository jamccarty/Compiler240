#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ParseFunctionHeader.h"

char** return_var_array(char *line, int linenum){
  char *whitespace = " \t\f\r\v\n";
  //char **array = malloc(sizeof(char *) * 50);
  char **array = (char**)calloc(50, sizeof(char));
  
  for(int i = 0; i < 50; i++){
    //array[i] = malloc(sizeof(char) * 150);
    array[i] = (char*)calloc(150, sizeof(char));
    //memset(array[i], (int)'\0', 149);
  }

  if (array == NULL) {
    printf("ERROR: calloc failed!\n");
    exit(1);
  }

  //why are we tokening again if the previous token was at the word we need to
  //put in the array?
  //Also random, but would we need to token again since the data isn't kept or
  //is it kept?
  char *token = strtok(NULL, whitespace);

  if(token == NULL){
    printf("Error: Formatting error on line %d\n", linenum);
    exit(1);
  }

  strcpy(array[0], token);

  token = strtok(NULL, whitespace);
  int numvars = 0;

  while(strcmp(token, ",") == 0){
    numvars++;
    token = strtok(NULL, whitespace);

    if(strtok(token, "int") != 0) {
      printf("Error: Formatting error on line %d\n", linenum);
      exit(1);
    }

    token = strtok(NULL, whitespace);
    strcpy(array[numvars], token);
    token = strtok(NULL, whitespace);

    if (strcmp(token, ")") == 0) {
      break;
    } else if (token == NULL) {
      printf("Formatting error on line %d - ';' expected\n", linenum);
      exit(1);
    }

    token = strtok(NULL, whitespace);
  }
  
  token = strtok(NULL, whitespace);

  if (strcmp(token, "{") == 0) {
    printf("Error: Add bracket after parentheses.\n");
    exit(1);
  }

  return array;

}