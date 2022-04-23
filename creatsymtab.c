#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Map.h"

char** parse_line(FILE *file, int *len) {
    rewind(file);
    if (file == NULL) {
        printf("Error with file.\n");
        exit(1);
    }
    
    char **array;
    char  *whitespace = " \t\f\r\v\n";
    char *token;
    char line[1000]; // = NULL;
    int j = 0;
    
    array = malloc(sizeof(char*) * 100);

    for (int i = 0; i < 100; i++) {
        array[i] = malloc(sizeof(char) * 150);
        memset(array[i], (int)'\0', 149);
    }

    if (array == NULL) {
        return NULL;
    }

    fgets(line,  100, file); //Get rid of function header

    while (fgets(line, 100, file) != NULL) {
        token = strtok(line, whitespace);
        if(strcmp(token, "return") == 0){
            *len = j;
            return array;
        } else if (strcmp(token, "int") != 0) {
            int fits = 0;
            for(int i = 0; i < j; i++){
                if(strcmp(token, array[i]) == 0){
                    fits = 1;
                }
            }
            if(fits == 0){
                printf("Error: Symbol %s has not been declared!\n", token);
            }
        } else {
            token = strtok(NULL, whitespace);
            if(token == NULL){
                *len = j;
                return array;
            }
            if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
            (strcmp(token, ",") == 0)) {
                printf("Error: Missing variable name!\n");
            } else {
                strcpy(array[j], token);
                j++;
            }

            token = strtok(NULL, whitespace);

            if ((strcmp(token, ";") != 0) && (strcmp(token, ",") != 0) &&
              (strcmp(token, "=") != 0)) {
              printf("Error: Variable names can't contain space!\n");
            }

            while (1) {
                if (strcmp(token, ",") == 0) {
                    token = strtok(NULL, whitespace);
                    if ((strcmp(token, ";") == 0) || (strcmp(token, "=") == 0) ||
                    (strcmp(token, ",") == 0)) {
                        printf("Error: Missing variable name!\n");
                    } else {
                        strcpy(array[j], token);
                        j++;
                    }

                    token = strtok(NULL, whitespace);
                    
                    if ((strcmp(token, ";") != 0) && (strcmp(token, ",") != 0) &&
                      (strcmp(token, "=") != 0)) {
                      printf("Error: Variable names can't contain space!\n");
                    }
                } else { 
                    break;
                }
            }

            if (strcmp(token, "=") == 0) {
                token = strtok(NULL, whitespace);

                if ((strcmp(token, ";") == 0) || (strcmp(token, ",") == 0) ||
                  (strcmp(token, "=") == 0) || (strcmp(token, "+") == 0)) {
                  printf("Error: Need value after assignment operator!\n");
                }
                
                token = strtok(NULL, whitespace);
                
                while (1) {
                    if (strcmp(token, ",") == 0) {
                        token = strtok(NULL, whitespace);
                        
                        if ((strcmp(token, ",") != 0) && (strcmp(token, ";") != 0) 
                            && (strcmp(token, "=") != 0) && (strcmp(token, "+") != 0)) {
                            strcpy(array[j], token);
                            j++;
                        } else {
                          printf("Error: Need value after assignment operator!\n");
                        }
                    } else if (strcmp(token, "=")) {
                        token = strtok(NULL, whitespace);
                        if ((strcmp(token, ",") != 0) && (strcmp(token, ";") != 0)
                            && (strcmp(token, "=") != 0) && (strcmp(token, "+") != 0)) {
                            token = strtok(NULL, whitespace);
                            if ((strcmp(token, ",") != 0) && (strcmp(token, ";") != 0)
                                && (strcmp(token, "+") != 0)) {
                                printf("Error: Need operator between values!\n");
                            }
                        }
                    } else if (strcmp(token, "+") == 0) {
                        token = strtok(NULL, whitespace);
                        
                        if ((strcmp(token, ",") == 0) || (strcmp(token, ";") == 0) 
                            || (strcmp(token, "=") == 0) || (strcmp(token, "+") == 0)) {
                          printf("Error: Need value after operator!\n");
                        }
                    } else if (strcmp(token, ";") == 0) {
                        break;
                    } else if ((strcmp(token, ";") != 0) && 
                      (strcmp(token, ",") != 0) && (strcmp(token, "=") != 0)) {
                      printf("Error: Variable names can't contain space!\n");
                    }

                    token = strtok(NULL, whitespace);
                }
            }
        }
        
        if (strcmp(token, ";") != 0) {
            printf("Error: Doesn't end with semicolon!\n");
        }

        if (strcmp(token, "return") == 0) {
            token = strtok(NULL, whitespace);
        }
    }
    
    *len = j;
    return array;
}

char** parse_function_header(FILE *file, int *len) {
    rewind(file);
    if (file == NULL) {
        printf("Error with file.\n");
        exit(1);
    }

    char **array;
    char *whitespace = " \t\f\r\v\n";
    char *token;
    char *line = NULL;
    int j = 0;
    
    array = malloc(sizeof(char*) * 100);

    for (int i = 0; i < 100; i++) {
        array[i] = malloc(sizeof(char) * 150);
        memset(array[i], (int)'\0', 149);
    }

    if (array == NULL) {
        return NULL;
    }

    line = malloc(sizeof(char) * 150);

    if (line == NULL) {
        printf("Error: malloc failed!\n");
    }

    fgets(line, 100, file);

    token = strtok(line, whitespace);
    if (strcmp(token, "int") != 0) {
        printf("Error: Need to declare return type for function!\n");
    }
    
    token = strtok(NULL, whitespace);
    if (strcmp(token, "(") == 0) {
        printf("Error: Missing a function name.\n");
    }

    token = strtok(NULL, whitespace);
    if (strcmp(token, "(") != 0) {
        printf("Error: Missing open parentheses for function's parameters.\n");
    }

    token = strtok(NULL, whitespace);
    while (token != NULL) {
        if (strcmp(token, ")") == 0) {
            break;
        } else if (strcmp(token, "int") != 0) {
            printf("Error: Missing parameter's variable type declaration.\n");
        } else {
            token = strtok(NULL, whitespace);
            if ((strcmp(token, "int") != 0) && (strcmp(token, ")") != 0) &&
                (strcmp(token, ",") != 0)) {
                strcpy(array[j], token);
                j++;
            } else {
                printf("Error: Missing variable name.\n");
            }
        }

        token = strtok(NULL, whitespace);

        if (strcmp(token, ")") == 0) {
            break;
        } else if ((strcmp(token, ",") != 0) && (strcmp(token, "int") != 0)) {
          printf("Error: Variable name can't contain space!\n");
        } else if (strcmp(token, ",") != 0) {
            printf("Error: Invalid parameter.\n");
        }

        token = strtok(NULL, whitespace);
    }

    free(line);
    line = NULL;
    
    *len = j;
    return array;
}

struct pair* create_symbol_table(FILE *file){
    if(file == NULL){
        printf("Error: file does not exist\n");
        exit(1);
    }

    char **params;
    char **local_vars;
    int params_len = 0, local_vars_len = 0;
    //int error = 0;

    params = parse_function_header(file, &params_len);//, &error);
    local_vars = parse_line(file, &local_vars_len);//, &error);

/*    if (error > 0) {
      exit(1);
    }*/
    
    int size = 2 * params_len + local_vars_len;
    struct pair *symbol_table = createMap(size);
    
    int poffset = 4;
    for(int i = 0; i < params_len; i++){
        mapAdd(symbol_table, params[i], poffset + i, size);
    }
    
    int loffset = 0;
    for(int i = 0; i < local_vars_len; i++){
        mapAdd(symbol_table, local_vars[i], loffset - i, size);
    }

    for (int i = 0; i < 100; i++) {
      free(params[i]);
      params[i] = NULL;
    }

    free(params);
    params = NULL;

    for (int i = 0; i < 100; i++) {
      free(local_vars[i]);
      local_vars[i] = NULL;
    }
    
    free(local_vars);
    local_vars = NULL;

    return symbol_table;
}

int main(int argc, char** argv){
    if (argc < 2){
        printf("Error: A filename must be entered.\n");
        exit(1);
    } else if (argc > 2) {
        printf("Error: Only one filename must be enterd.\n");
        exit(1);
    }
    
    FILE *file = fopen(argv[1], "r");
    struct pair *symbol_table = create_symbol_table(file);
    char *string = mapToString(symbol_table, sizeof(symbol_table));
    printf("%s\n", string);

    free(symbol_table);
    symbol_table = NULL;
    
    free(string);
    string = NULL;
    
    
    fclose(file);
    return 0;
}
