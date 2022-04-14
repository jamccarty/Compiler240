#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "match_braces.h"

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

char** parse_function_header(char* line, int linenum){
  char *whitespace = " \t\f\r\v\n";
  char *token = strtok(line, whitespace);
  char **array;

  if (strcmp(token, "int") != 0) {
    printf("Error: function is missing return type.\n");
    exit(1);
  }

  token = strtok(line, whitespace);

  while (token != NULL) {
    if (strcmp(token, "(") == 0) {
      token = strtok(NULL, whitespace);

      if (token == NULL) {
        printf("Error: No parameters!\n");
        exit(1);
      } else if (strcmp(token, "int") != 0) {
        printf("Error: No declaration!\n");
        exit(1);
      }
      array = return_var_array(line, linenum);
    }
    token = strtok(NULL, whitespace);
  }

  if (array[0][0] == 0) { //wouldn't this mean the array has to be calloced for 0?
    return NULL;
  }

  return array;
}

char** parse_line_programs(FILE *file){
  char *whitespace = " \t\f\r\v\n";
  char *line = malloc(sizeof(char) * 150);

  if(line == NULL){
    printf("Unable to allocate line\n");
    exit(1);
  }
  char **all_vars = malloc(sizeof(char*) * 150);
  ssize_t characters;
  ssize_t linesize = 150;
  int linenum = 0;

  characters = getline(&line, &linesize, file);

  while(characters != -1){
    char** line_vars;
    linenum++;
    line_vars = parse_function_header(line, linenum);
    
    if(line_vars == NULL){
      char *token = strtok(line, whitespace);
  
      if(token == NULL){
        printf("Error\n");
        exit(1);
      }

      if(strcmp(token, "int") == 0){
        line_vars = return_var_array(line, linenum);
      }
    }
    characters = getline(&line, &linesize, file);
  }
  
  return all_vars;
}

int main(int argc, char** argv){
  int enough_braces;

  if(argc != 2) {
    printf("ERROR: no file inputted\n");
    exit(1);
  }

  int len = strlen(argv[1]);
  char *compiled_name = malloc(sizeof(char) * (len + 3));
    //memset(compiled_name, 0, len + 4);
  strcpy(compiled_name, argv[1]);
  strtok(compiled_name, ".");
  strcat(compiled_name, ".asm");

  FILE *og_file = fopen(argv[1], "r");
  enough_braces = check_braces(og_file, argv[1]);
  FILE *comp_file = fopen(compiled_name, "w");


  if(og_file == NULL) {
    printf("Eror: could not find file %s\n", argv[1]);
    exit(1);
  }
  
  if(comp_file == NULL) {
    printf("Error: could not compile file\n");
    exit(1);
  }
  
  if(enough_braces == 1) {
    exit(1);
  }
  
  return 0;
}