#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Map.h"

char  *whitespace = " \t\f\r\v\n";

char** parse_line(FILE *file, char** array, int *len, int* err) {
  int errors = *err;
  rewind(file);
    
  if (file == NULL) {
    printf("Error with file.\n");
    exit(1);
  }

  char *token, *hold_token;
  char line[100];
  int j = 0;

  memset(line, '\0', 100);
    
  fgets(line,  100, file); //Gets rid of function header
  int linenumber = 1;

  while (fgets(line, 100, file) != NULL) {
    linenumber++;
    token = strtok(line, whitespace);

    if (strcmp(token, "}") == 0) {
      break;
    }

    if(strcmp(token, "return") == 0){
      token = strtok(NULL, whitespace);
      if ((strcmp(token, ";") != 0) && (strcmp(token, "=") != 0) &&
        (strcmp(token, ",") != 0) && (strcmp(token, "+") != 0)) {
        token = strtok(NULL, whitespace);
        if (token == NULL) {
          printf("ERROR on line %d: Doesn't end with semicolon!\n", linenumber);
          errors++;
        } else if (strcmp(token, "+") == 0) {
          token = strtok(NULL, whitespace);
          if (strcmp(token, ";") == 0) {
            printf("ERROR on line %d: Need value after addition operator!\n", linenumber);
            errors++;
          }
        }
      } else {
        printf("ERROR on line %d: Missing variable name!\n", linenumber);
        errors++;
      }
    } else if (strcmp(token, "int") != 0) {
      int fits = 0;
      for(int i = 0; i < j; i++){
        if(strcmp(token, array[i]) == 0){
          fits = 1;
        }
      }

      if(fits == 0){
        if(strcmp(token, "=") == 0){
          printf("ERROR on line %d: Missing variable name!\n", linenumber);
        } else {
          hold_token = token;
          token = strtok(NULL, whitespace);
          
          if ((strcmp(token, ";") != 0) && (strcmp(token, "=") != 0) &&
            (strcmp(token, ",") != 0) && (strcmp(token, "+") != 0) &&
            (strcmp(hold_token, ";") != 0) && (strcmp(hold_token, "=") != 0) &&
            (strcmp(hold_token, ",") != 0) && (strcmp(hold_token, "+") != 0)) {
            printf("ERROR on line %d: Illegal type \"%s\"\n", linenumber, hold_token);
          } else if (strcmp(token, "=") == 0) {
            token = strtok(NULL, whitespace);
            while (1) {
              if ((strcmp(token, ";") != 0) && (strcmp(token, "=") != 0) &&
                (strcmp(token, ",") != 0) && (strcmp(token, "+") != 0)) { 
                token = strtok(NULL, whitespace);
                if (strcmp(token, "+") == 0) {
                  token = strtok(NULL, whitespace);
                  if ((strcmp(token, ";") == 0) || (strcmp(token, ",") == 0) ||
                    (strcmp(token, "+") == 0) || (token == NULL)) {
                    printf("ERROR on line %d: Need value after addition operator!\n", linenumber);
                    errors++;
                    break;
                  }
                }
              }
            }
          }
/* else {
            printf("ERROR on line %d: Symbol %s has not been declared!\n", linenumber, hold_token);
          }*/
        }
        errors++;
        token = hold_token;
        continue;
      }
      
      token = strtok(NULL, whitespace);
      if (strcmp(token, "=") == 0) {
        token = strtok(NULL, whitespace);
        
        if (strcmp(token, "+") == 0) {
          printf("ERROR on line %d: Need value before addition operator!\n", linenumber);
          errors++;
        } else if ((strcmp(token, ";") == 0) || (strcmp(token, ",") == 0)) {
          printf("ERROR on line %d: Missing variable!\n", linenumber);
          errors++;
        } else if ((strcmp(token, ";") != 0) && (strcmp(token, "=") != 0) &&
          (strcmp(token, ",") != 0) && (strcmp(token, "+") != 0)) {
          token = strtok(NULL, whitespace);
          if (token == NULL) {
            printf("ERROR on line %d: Doesn't end with semicolon!\n", linenumber);
            errors++;
          } else if (strcmp(token, "+") == 0) {
            token = strtok(NULL, whitespace);
            if ((strcmp(token, ";") == 0) || (strcmp(token, ",") == 0) ||
              (strcmp(token, ",") == 0) || (strcmp(token, "+") == 0) || (token == NULL)) {
              printf("ERROR on line %d: Need value after addition operator!\n", linenumber);
              errors++;
            } 
          }
        }
      }
    } else {
      token = strtok(NULL, whitespace); //variable name
      if(token == NULL){ //if no variable name
        printf("ERROR on line %d: Missing variable name\n", linenumber);
        errors++;
        continue;
      }

      if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
        (strcmp(token, ",") == 0)) {
        printf("ERROR on line %d: Missing variable name!\n", linenumber);
        errors++;
        continue;
      } else {
        strcpy(array[j], token);
        j++;
      }

      token = strtok(NULL, whitespace);

      if(token == NULL){
        printf("ERROR on line %d: Doesn't end with semicolon!\n", linenumber);
        errors++;
        continue;
      }

      if ((strcmp(token, ";") != 0) && (strcmp(token, ",") != 0) &&
        (strcmp(token, "=") != 0)) {
        printf("ERROR on line %d: Variable names can't contain space!\n", linenumber);
        errors++;
        continue;
      }

      while (1) {
        if (strcmp(token, ",") == 0) {
          token = strtok(NULL, whitespace);
          if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
            (strcmp(token, ",") == 0)) {
            printf("ERROR on line %d: Missing variable name!\n", linenumber);
            errors++;
            continue;
          } else {
            strcpy(array[j], token);
            j++;
          }

          token = strtok(NULL, whitespace);

          if ((strcmp(token, ";") != 0) && (strcmp(token, ",") != 0) &&
            (strcmp(token, "=") != 0)) {
            printf("ERROR on line %d: Variable names can't contain space!\n", linenumber);
            errors++;
            break;
          }
        } else if(strcmp(token, "+") == 0){
          token = strtok(NULL, whitespace);
          if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
            (strcmp(token, ",") == 0)) {
            printf("ERROR on line %d: Need value after addition operator!\n", linenumber);
            errors++;
            break;
          }
            
          token = strtok(NULL, whitespace);
          if ((strcmp(token, ";") != 0) && (strcmp(token, ",") != 0) &&
            (strcmp(token, "=") != 0) && (strcmp(token, "+") != 0)) {
            printf("ERROR on line %d: Variable names can't contain space!\n", linenumber);
            errors++;
            break;
          }
        } else { 
          break;
        }
      }

      if (strcmp(token, "=") == 0) {
        token = strtok(NULL, whitespace);
        if ((strcmp(token, ";") == 0) || (strcmp(token, ",") == 0) ||
          (strcmp(token, "=") == 0) || (strcmp(token, "+") == 0)) {
          printf("ERROR on line %d: Need value after assignment operator!\n", linenumber);
          errors++;
          continue;
        }

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
          } else if ((strcmp(token, ";") != 0) && (strcmp(token, ",") != 0)
            && (strcmp(token, "=") != 0) && strcmp(token, "+") != 0) {
            printf("ERROR on line %d: Need operator between values!\n", linenumber);
            errors++;
            token = strtok(NULL, whitespace);
            continue;
          }

          token = strtok(NULL, whitespace);
        }
      }
    }
  }

  *err = errors;
  *len = j;
  return array;
}

char** parse_function_header(FILE *file, char** array, int *len, int *err){
  int errors = *err;
  rewind(file);
  if (file == NULL) {
    printf("Error with file.\n");
    exit(1);
  }

  char *token;
  char line[100];
  int j = 0;

  fgets(line, 100, file);

  token = strtok(line, whitespace);
  if (strcmp(token, "int") != 0) {
    printf("ERROR on line 1: Need to declare return type for function!\n");
    errors++;
  }
    
  token = strtok(NULL, whitespace);
  if (strcmp(token, "(") == 0) {
    printf("ERROR on line 1: Missing a function name.\n");
    errors++;
  }

  token = strtok(NULL, whitespace);
  if (strcmp(token, "(") != 0) {
    printf("ERROR on line 1: Missing open parentheses for function's parameters.\n");
    errors++;
  }

  token = strtok(NULL, whitespace);
  while (token != NULL) {
    if (strcmp(token, ")") == 0) {
      break;
    } else if (strcmp(token, "int") != 0) {
      printf("ERROR on line 1: Missing parameter's variable type declaration.\n");
      errors++;
      continue;
    } else {
      token = strtok(NULL, whitespace);
      if ((strcmp(token, "int") != 0) && (strcmp(token, ")") != 0) &&
        (strcmp(token, ",") != 0)) {
         strcpy(array[j], token);
         j++;
       } else {
         printf("ERROR on line 1: Missing variable name.\n");
         errors++;
         continue;
      }
    }

    token = strtok(NULL, whitespace);
    if (strcmp(token, ")") == 0) {
      break;
    } else if ((strcmp(token, ",") != 0) && (strcmp(token, "int") != 0)) {
      printf("ERROR on line 1: Variable name can't contain space!\n");
      errors++;
      continue;
    } else if (strcmp(token, ",") != 0) {
      printf("ERROR on line 1: Invalid parameter.\n");
      errors++;
      continue;
    }

    token = strtok(NULL, whitespace);
  }
    
  *len = j;
  *err = errors;
   
  return array;
}

struct pair* createSymbolTable(FILE *file, int *size, int *isErrors){
  if(file == NULL){
    printf("ERROR: file does not exist\n");
    exit(1);
  }

  int errors = 0;
  char **params;
  int params_len = 0;
  char **local_vars;
  int local_vars_len = 0;

  params = malloc(sizeof(char*) * 100);
  for (int i = 0; i < 100; i++) {
    params[i] = malloc(sizeof(char) * 100);
    memset(params[i], (int)'\0', 99);
  }

  if (params == NULL) {
    return NULL;
  }

  local_vars = malloc(sizeof(char*) * 100);
  for (int i = 0; i < 100; i++) {
    local_vars[i] = malloc(sizeof(char) * 100);
    memset(local_vars[i], (int)'\0', 99);
  }

  if (local_vars == NULL) {
    return NULL;
  }

  params = parse_function_header(file, params, &params_len, &errors);
  local_vars = parse_line(file, local_vars, &local_vars_len, &errors);

  if(errors > 0){
    printf("%d errors found\n", errors);
    *isErrors = 1;
  }

  *size = 2 * (params_len + local_vars_len);
  struct pair *symbol_table = createMap(*size);

  int poffset = 4;
  for(int i = 0; i < params_len; i++){
    mapAdd(symbol_table, params[i], poffset + i, *size);
  }
    
  int loffset = 0;
  for(int i = 0; i < local_vars_len; i++){
    mapAdd(symbol_table, local_vars[i], loffset - i, *size);
  }

  for(int i = 0; i < 100; i++){
    free(params[i]);
    params[i] = NULL;
  }
  free(params);
  params = NULL;

  for(int i = 0; i < 100; i++){
    free(local_vars[i]);
    local_vars[i] = NULL;
  }
  free(local_vars);
  local_vars = NULL;

  return symbol_table;
}

//writes required instructions for adding 2+ numbers in LC-3 code to LC3 string 
//(which will be eventually printed to assembly code file)
//params:   symbol_table = map containing all declared local variables and parameters in function
//          symbol_table_size = size of symbol_table (NOTE: *not* the number of variables stored)
//          current_line = string containing original addition instruction ( i.e. x = y + 3 ; )
//          LC3 = string containing entirety of LC-3 assembly code, to be printed to file after compilation is completed
//          errors = number of errors found during compilation process. if errors > 0 by end, LC3 file will not be created
//          linenum = current linenumber in source code file
void add(struct pair *symbol_table, const int symbol_table_size, char *current_line, char *LC3, int *err, int linenum){
    int errors = *err;
    //for example code: assume current_line is "x = y + 3 ;"
    char *token = strtok(current_line, whitespace); //token now holds either "int" or variable name
    char store_var[100];
    char add[1024];
    memset(store_var, '\0', 100);
    memset(add, '\0', 1024);

    if(strcmp(token, "int") == 0){ //if token == "int", skips it. token now holds variable name
        token = strtok(current_line, whitespace);
    }

    strcpy(store_var, token); //store_var now holds variable sum will be stored at

    //THIS IS NOT WORKING RIGHT??????????????????????????????????????????????????
    if(mapGetValue(symbol_table, token, symbol_table_size) == 1){ //if token does not exist in symbol_table, print error
        printf("ERROR on line %d: variable '%s' has not been declared\n", linenum, token);
        errors++;
    }

    token = strtok(NULL, whitespace); //token now holds "="
    token = strtok(NULL, whitespace); //token now holds either variable or number

    if(token[0] >= '0' && token[0] <= '9'){ //if token is a literal number, load into current register
        //NOTE: LC3 registers hold 5-bit two's compliment

            int num = atoi(token);
            while(num >= 15){
                sprintf(add, "ADD R0, R0, #15\n");
                strcat(LC3, add);
                num = num - 15;
            }

            while(num <= -16){
                sprintf(add, "ADD R0, R0, #-16\n");
                strcat(LC3, add);
                num = num + 16;
            }

            sprintf(add, "ADD R0, R0, #%d\n", num);
            strcat(LC3, add);

        }else if(mapGetValue(symbol_table, token, symbol_table_size) == 1){ //if token does not exist in symbol_table, print error
            printf("ERROR on line %d: variable '%s' has not been declared\n", linenum, token);
            errors++;
        }else{
            sprintf(add, "LDR R0, R5, %s\n", token); //(from example): add onto LC3 code - load y into R0
            strcat(LC3, add);
        }

    while(token != NULL){
        token = strtok(NULL, whitespace); //token should now hold "+"

        if(strcmp(token, "+") != 0){
            printf("ERROR on line %d: illegal operand '%s'\n", linenum, token);
            errors++;
        }

        token = strtok(NULL, whitespace); //get next variable

        if(token[0] <= '0' && token[0] >= '9'){ //if token is a literal number, load into current register
        //NOTE: LC3 registers hold 5-bit two's compliment

            int num = atoi(token);
            while(num >= 15){
                sprintf(add, "ADD R1, R1, #15\n");
                strcat(LC3, add);
                num = num - 15;
            }

            while(num <= -16){
                sprintf(add, "ADD R1, R1, #-16\n");
                strcat(LC3, add);
                num = num + 16;
            }

            sprintf(add, "ADD R1, R1, #%d\n", num);
            strcat(LC3, add);

        }else if(mapGetValue(symbol_table, token, symbol_table_size) == 1){ //if token does not exist in symbol_table, print error
            printf("ERROR on line %d: variable '%s' has not been declared\n", linenum, token);
            errors++;
        }else{
            sprintf(add, "LDR R0, R5, %s\n", token); //(from example): add onto LC3 code - load y into R0
            strcat(LC3, add);
        }

        sprintf(add, "ADD R0, R0, R1\n"); //add contents of R0 and R1, store in R0
        strcat(LC3, add);
    }

    sprintf(add, "STR, R0, R5, %s\n", store_var);
    strcat(LC3, add);
    *err = errors;
    return;
}

char *read_operations(FILE *file, struct pair *symbol_table, int symbol_table_size, int *errors){
    rewind(file);
    char current_line[200];
    char hold_line[200];
    memset(current_line, '\0', 200);
    memset(hold_line, '\0', 200);
    char *LC3 = malloc(sizeof(char) * (1024));
    memset(LC3, '\0', 1024);

    fgets(current_line, 1024, file);
    strcpy(hold_line, current_line);
    char *token = strtok(current_line, whitespace);
    int linenum = 1;

    while (current_line != NULL) {
        token = strtok(current_line, whitespace);
        while(token != NULL){
            if(strcmp(token, "+") == 0){
                add(symbol_table, symbol_table_size, hold_line, LC3, errors, linenum);
            }
            token = strtok(NULL, whitespace);
        }
        linenum++;
        fgets(current_line, 200, file);
        strcpy(hold_line, current_line);

    }
    return LC3;
}

int main(int argc, char** argv){
  if(argc < 2){
    printf("Error: A filename must be entered.\n");
    exit(1);
  }
    
  FILE *file = fopen(argv[1], "r");
  char *LC3;
  int size;
  int isErr = 0;
  struct pair *symbol_table = createSymbolTable(file, &size, &isErr);
  LC3 = read_operations(file, symbol_table, size, &isErr);
    
  if (isErr == 1){
    free(symbol_table);
    symbol_table = NULL;
    fclose(file);
    exit(1);
  }

  char *string = mapToString(symbol_table, size);
  printf("%s\n%s\n", LC3, string);

  free(symbol_table);
  symbol_table = NULL;
  free(string);
  string = NULL;
  fclose(file);
  free(LC3);
  LC3 = NULL;
  
  return 0;
}
