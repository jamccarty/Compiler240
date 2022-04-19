#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char** parse_line(FILE *file, int *len) {
    rewind(file);
    if (file == NULL) {
        printf("Error with file.\n");
        exit(1);
    }
    char  *whitespace = " \t\f\r\v\n";
    char *token;
    char **array;
    char *line = NULL;
    int j = 0;

    line = malloc(sizeof(char) * 100);
    memset(line, '\0', 100);
    
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
    line = fgets(line,  100, file); //get rid of function header
    while (fgets(line, 100, file) != NULL) {
        token = strtok(line, whitespace);
        if(strcmp(token, "return") == 0){
            *len = j;
            return array;
        }else if (strcmp(token, "int") != 0) {
            int fits = 0;
            for(int i = 0; i < j; i++){
                if(strcmp(token, array[i]) == 0){
                    fits = 1;
                }
            }
            if(fits == 0){
                printf("ERROR: symbol %s has not been declared\n", token);
                exit(1);
            }
        }else{
            token = strtok(NULL, whitespace);
            if(token == NULL){
                *len = j;
                return array;
            }
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
    }

    free(line);
    line = NULL;

    *len = j;
    return array;
}



char** parse_function_header(FILE *file, int *len){
    rewind(file);
    if (file == NULL) {
        printf("Error with file.\n");
        exit(1);
    }

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
    
    *len = j;
    return array;
}

char* createSymbolTable(FILE *file){
    if(file == NULL){
        printf("ERROR: file does not exist\n");
        exit(1);
    }

    char* symbol_table = malloc(sizeof(char) * 500);
    memset(symbol_table, '\0', 500);

    char **params;
    int params_len;
    char **local_vars;
    int local_vars_len;

    params = parse_function_header(file, &params_len);
    local_vars = parse_line(file, &local_vars_len);

    int poffset = 4;
    char *newline = malloc(sizeof(char) * 50);
    memset(newline, '\0', 50);
    for(int i = 0; i < params_len; i++){
        sprintf(newline, "%s +%d\n", params[i], poffset + i);
        strcat(symbol_table, newline);
    }
    
    int loffset = 0;
    for(int i = 0; i < local_vars_len; i++){
        sprintf(newline, "%s %d\n", local_vars[i], loffset - i);
        strcat(symbol_table, newline);
    }
    free(newline);
    newline = NULL;

    return symbol_table;
}

int main(int argc, char** argv){
    if(argc < 2){
        printf("Error: A filename must be entered.\n");
        exit(1);
    }
    FILE *file = fopen(argv[1], "r");
    char *symbol_table = createSymbolTable(file);
    printf("%s\n", symbol_table);
}