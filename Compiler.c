#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <ctype.h>
#include "Map.h"

char *whitespace = " \t\f\r\v\n";

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
void assign(struct pair *symbol_table, const int symbol_table_size, char *current_line, char *LC3, int *err, int linenum){
  int errors = *err;
  //for example code: assume current_line is "x = y + 3 ;"
  char *token = strtok(current_line, whitespace); //token now holds either "int" or variable name
  char store_var[100];
  char add[1024];
  memset(store_var, '\0', 100);
  memset(add, '\0', 1024);
  int changeReg = 0, changeReg2 = 0, change = 0;
  int chr = 0, isChanged = 0;

  //TODO if(strcmp(token, "int") == 0 || strcmp(token, "return") ==0)
  if (strcmp(token, "int") == 0) { //if token == "int", skips it. token now holds variable name
    token = strtok(NULL, whitespace);
  }

  strcpy(store_var, token); //store_var now holds variable sum will be stored at

  if (mapGetValue(symbol_table, token, symbol_table_size) == 1) { //if token does not exist in symbol_table, print error
      printf("ERROR on line %d: variable '%s' has not been declared\n", linenum, token);
      errors++;
    //}
  } else {
    token = strtok(NULL, whitespace); //token now holds "="
    token = strtok(NULL, whitespace); //token now holds either variable or number

    while (token != NULL) { 
      //tried isdigit() instead of strcmp'ing for every value between 0-15, but it kept giving errors with isdigit() so changed to the more tedious way (;-;)
      if ((strcmp(token, "0") == 0) || (strcmp(token, "1") == 0) || (strcmp(token, "2") == 0) ||
        (strcmp(token, "3") == 0) || (strcmp(token, "4") == 0) || (strcmp(token, "5") == 0) ||
        (strcmp(token, "6") == 0) || (strcmp(token, "7") == 0) || (strcmp(token, "8") == 0) ||
        (strcmp(token, "9") == 0) || (strcmp(token, "10") == 0) || (strcmp(token, "11") == 0) ||
        (strcmp(token, "12") == 0) || (strcmp(token, "13") == 0) || 
        (strcmp(token, "14") == 0) || (strcmp(token, "15") == 0)) {
        //if token is a literal number, load into current register
        //NOTE: LC3 registers hold 5-bit two's compliment
        
        int num = atoi(token);
        token = strtok(NULL, whitespace);
        if (strcmp(token, "+") == 0) {
          changeReg2 = 1;
        }
        
        if ((changeReg == 1) && (changeReg2 == 1)) {
          change = 1;
        }
        sprintf(add, "AND R%d, R%d, #0\n", change, change);
        strcat(LC3, add);
        //changeReg = 1;
        
        sprintf(add, "ADD R%d, R%d, #%d\n", change, change, num);
        strcat(LC3, add);
      } else {
        if (mapGetValue(symbol_table, token, symbol_table_size) == 1){
        //if token does not exist in symbol_table, print error
          printf("ERROR on line %d: variable '%s' has not been declared\n", linenum, token);
          errors++;
        } else {
          //First find where the varible is in the symbol table then add the symbol's key (which is the offset)!!!!!!!
          char* token2 = token;
          token = strtok(NULL, whitespace);

          //The thing below for %s should be taking in the offset NOT the token!!
          sprintf(add, "LDR R%d, FP, %s\n", chr, token2); //(from example): add onto LC3 code - load y into R0
          strcat(LC3, add);
          if (strcmp(token, "+") == 0) {
            chr = 1;
            change = 1;
            //printf("LOL\n");
          }
          isChanged = 1;
        }
      }
      
      if ((strcmp(token, "+") == 0) || (strcmp(token, ",") == 0)) {
        printf("NORRRRRRRRRRRRR\n");
        if (strcmp(token, "+") == 0) {
          changeReg = 0;
        }
        token = strtok(NULL, whitespace);
        printf("%s\n", token);
      } else if ((strcmp(token, "+") != 0) && (strcmp(token, ";") != 0) && (strcmp(token, ",") != 0)) {
        printf("ERROR on line %d: Invalid code format involving \"%s\"\n", linenum, token);
        errors++;
        break;
      }
  
      if (strcmp(token, ";") == 0) {
        if (isChanged == 1) {
          sprintf(add, "ADD R0, R0, R1\n");
          strcat(LC3, add);
        }
        //STORE_VAR SHOULD BE THE TOKEN NOT HT EACTUAL VARIABLEEEE!!!
        sprintf(add, "STR R0, FP, %s\n", store_var);
        strcat(LC3, add);
        token = strtok(NULL, whitespace);
      }
    }
  }
  
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
    fgets(current_line, 1024, file); //fgets twice to skip first function header line
    strcpy(hold_line, current_line);
    char *token;// = strtok(current_line, whitespace);
    int linenum = 1;
    
  
    while (current_line != NULL) {
      char semicol[] = "\n;";  
      strcat(semicol, current_line);
      strcat(semicol, ";\n");
      strcat(LC3, semicol);

      token = strtok(current_line, whitespace);
      if(strcmp(token, "return") == 0) {
        break;
      } else if (strcmp(token, "}") != 0) {
        assign(symbol_table, symbol_table_size, hold_line, LC3, errors, linenum);
      } else {
        break;
      }
     
      linenum++;
      fgets(current_line, 200, file);
      strcpy(hold_line, current_line);
    }

    return LC3;
}

int main(int argc, char** argv) {
  if(argc < 2){
    printf("Error: A filename must be entered.\n");
    exit(1);
  } else if (argc > 2) {
    printf("Error: Only one filename must be entered.\n");
    exit(1);
  }
    
  FILE *file = fopen(argv[1], "r");
  if (file == NULL) {
    printf("Error: Unable to open file%s\n", argv[1]);
    exit(1);
  }

  FILE *fp;
  int size;
  int isErr = 0;
  char *LC3 = NULL;
  LC3 = malloc(sizeof(char) * 4000);

  if (LC3 == NULL) {
    printf("Error: malloc has failed.\n");
    exit(1);
  }

  struct pair *symbol_table = createSymbolTable(file, &size, &isErr);
  LC3 = read_operations(file, symbol_table, size, &isErr);
    
  if (isErr == 1) {
    free(symbol_table);
    symbol_table = NULL;
    fclose(file);
    exit(1);
  }

  char *string = mapToString(symbol_table, size);
  printf("%s\n%s\n", LC3, string);

  fp = fopen("LC3.asm", "w+");
  if (fp == NULL) {
    printf("Error: malloc has failed.\n");
    exit(1);
  }

  fputs(LC3, fp);
  
  free(LC3);
  LC3 = NULL;
  free(symbol_table);
  symbol_table = NULL;
  free(string);
  string = NULL;
  //free(LC3);
  //LC3 = NULL;
  fclose(file);
  fclose(fp);

  return 0;
}
