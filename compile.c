#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "match_braces.h"

char** parse_function_header(FILE *file){

}

char* parse_line_programs(char *line, char type, void *stored){
    char *whitespace = " \t\f\r\v\n";
    char *token;
    char *var_name;
    token = strtok(line, whitespace);
    while(token != NULL){
        if(token == "int"){
            type = 'i';

        }
    }
}

int main(int argc, char** argv){
    int enough_braces;
    if(argc != 2){
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


    if(og_file == NULL){
        printf("ERROR: could not find file %s\n", argv[1]);
        exit(1);
    }
    if(comp_file == NULL){
        printf("ERROR: could not compile file\n");
        exit(1);
    }
    if(enough_braces == 1){
        exit(1);
    }

    return 0;
}