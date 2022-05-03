#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char** parse_function_header(FILE *filename, int *err) {
  rewind(filename);

  char *whitespace = " \t\f\r\v\n";
  char *token;
  char **array;
  char line[1000];// = NULL;
  int j = 0;

/*  token = malloc(sizeof(char) * 100);
  
  if (token == NULL) {
    printf("Error: malloc failed!\n");
    exit(1);
  }
*/
  array = malloc(sizeof(char*) * 100);

  for (int i = 0; i < 100; i++) {
    array[i] = malloc(sizeof(char) * 150);
    memset(array[i], (int)'\0', 149);
  }

  if (array == NULL) {
    return NULL;
  }

  fgets(line, 100, filename);
  
  token = strtok(line, whitespace);

  if (strcmp(token, "int") != 0) {
    printf("Error: Need to declare return type for function!\n");
    err++;
  }

  token = strtok(NULL, whitespace);

  if (strcmp(token, "(") == 0) {
    printf("Error: Missing a function name.\n");
    err++;
  }

  token = strtok(NULL, whitespace);

  if (strcmp(token, "(") != 0) {
    printf("Error: Missing open parentheses for function's parameters.\n");
    err++;
  }

  token = strtok(NULL, whitespace);

  while (token != NULL) {
    if (strcmp(token, ")") == 0) {
      break;
    } else if (strcmp(token, "int") != 0) {
      printf("Error: Missing parameter's variable type declaration.\n");
      err++;
    } else {
      token = strtok(NULL, whitespace);
  
      if ((strcmp(token, "int") != 0) && (strcmp(token, ")") != 0) &&
        (strcmp(token, ",") != 0)) {
        strcpy(array[j], token);
        j++;
      } else {
        printf("Error: No variable name declared.\n");
        err++;
      }
    }

    token = strtok(NULL, whitespace);
    if (strcmp(token, ")") == 0) {
      break;
    } else if (strcmp(token, ",") != 0) {
      printf("Error: Invalid parameter.\n");
      err++;
    }
      
    token = strtok(NULL, whitespace);
  }
    
  //free(token);
  //token = NULL;

  return array;
}

char** parse_line(FILE* filename, int *err) {
  rewind(filename);
  char *whitespace = " \t\f\r\v\n";
  char *token;
  char **array;
  char line[100];// = NULL;
  int j = 0;

 /* token = malloc(sizeof(char) * 100);

  if (token == NULL) {
    printf("Error: malloc failed!\n");
    exit(1);
  }*/

  array = malloc(sizeof(char*) * 100);

  for (int i = 0; i < 100; i++) {
    array[i] = malloc(sizeof(char) * 150);
    memset(array[i], (int)'\0', 149);
  }

  if (array == NULL) {
    return NULL;
  }

  fgets(line, 100, filename);

  while (fgets(line, 100, filename) != NULL) {
    token = strtok(line, whitespace);
    if (strcmp(token, "int") != 0) {
      printf("Error: Need to declare variable type!\n");
      exit(1);
    }
  
    token = strtok(NULL, whitespace);
    if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
      (strcmp(token, ",") == 0)) {
      printf("Error: Need to declare variable name!\n");
      exit(1);
    } else {
      strcpy(array[j], token);
      j++;
    }

    token = strtok(NULL, whitespace);

    while (1) {
      if (strcmp(token, ",") == 0) {
        token = strtok(NULL, whitespace);
        if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
          (strcmp(token, ",") == 0)) {
          printf("Error: Need to declare variable name!\n");
          exit(1);
        } else {
          strcpy(array[j], token);
          j++;
        }

        token = strtok(NULL, whitespace);
      } else {
        break;
      }
    }

    if (strcmp(token, "=") == 0) {
      token = strtok(NULL, whitespace);
      token = strtok(NULL, whitespace);
      while (1) {
        if (strcmp(token, ",") == 0) {
        token = strtok(NULL, whitespace);
        strcpy(array[j], token);
        j++;
        } else if (strcmp(token, "+") == 0) {
          token = strtok(NULL, whitespace);
        } else if (strcmp(token, ";") == 0) {
          break;
        }
        token = strtok(NULL, whitespace);
      }
    }
  }

  //free(token);
  //token = NULL;

  return array;
}

int main(int argc, char** argv) {
  char **param_header_array, **param_array;
  int i = 0, error = 0;

  if (argc < 2) {
    printf("Error: A filename must be entered.\n");
    exit(1);
  } else if (argc > 2) {
    printf("Error: Only one filename must be entered.\n");
    exit(1);
  }

  FILE *file = fopen(argv[1], "r");

  if (file == NULL) {
    printf("Error: Unable to open file %s\n", argv[1]);
    exit(1);
  }

  param_header_array = parse_function_header(file, &error);
  param_array = parse_line(file, &error);

  if (error > 0) {
    exit(1);
  }

  if (param_header_array[i][0] != '\0') {
    printf("All function parameter names: \n");
    
    while (param_header_array[i][0] != '\0') {
      printf("%s\n", param_header_array[i]);
      i++;
    }
  } else {
    printf("There are no function parameter names.\n");
  }

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
    free(param_header_array[j]);
    param_header_array[j] = NULL;
  }

  free(param_header_array);
  param_header_array = NULL;

  for (int j = 0; j < 100; j++) {
    free(param_array[j]);
    param_array[j] = NULL;
  }

  free(param_array);
  param_array = NULL;

  fclose(file);

  return 0;
}
