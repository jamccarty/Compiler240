#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_line(const char* filename) {
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

  while (line != NULL) {
    token = strtok(line, whitespace);

    if(token == NULL){
      break;
    }

    printf("%s\n", token);
    if (strcmp(token, "int") != 0) {
      printf("Error: Need to declare variable type!\n");
      exit(1);
    }
    
    token = strtok(NULL, whitespace);

    if(token == NULL){
      break;
    }

    if ((strcmp(token, ";") == 0) || (strcmp(token, ",") == 0) ||
      (strcmp(token, "=") == 0)) {
      printf("Error: Need to declare variable name!\n");
      exit(1);
    } else {
      strcpy(array[j], token);
      j++;
    }

    token = strtok(NULL, whitespace);
    if(token != NULL){
      while (strcmp(token, ",") == 0) {
        if ((strcmp(token, "=") == 0) || (strcmp(token, ";") == 0)) {
          printf("Error: Need to declare variable name!\n");
          exit(1);
        }
        
        token = strtok(NULL, whitespace);
        strcpy(array[j], token);
        j++;
      
        token = strtok(NULL, whitespace);
      } 
      
      if (strcmp(token, "=") == 0) {
        //NEED TO HANDLE NUMBERS AND CHECK IF A VARIABLE EQUALS A VARIABLE THAT
        //THE VARIABLE IS DECLARED.
      }
    }
    
    fgets(line, 100, file);
    //free(templine);
    //templine = NULL;
  }

  free(line);
  line = NULL;
  
  fclose(file);

  return array;
}

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

  param_array = parse_line(argv[1]);
  
  if (param_array[i][0] != '\0') {
    printf("All variable names declared: \n");
    
    while (param_array[i][0] != '\0') {
      printf("%s\n", param_array[i]);
      i++; 
    }
  } else {
    printf("There are no variable names declared.\n");
  }

  for (int j = 0; j < 100; j++) {
    free(param_array[j]);
    param_array[j] = NULL;
  }

  free(param_array);
  param_array = NULL; 
  return 0;
}
