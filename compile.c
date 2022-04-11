#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* parse_function_header(){

}

int main(int argc, char** argv){
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
    FILE *comp_file = fopen(compiled_name, "w");


    if(og_file == NULL){
        printf("ERROR: could not find file %s\n", argv[1]);
    }
    if(comp_file == NULL){
        printf("ERROR: could not compile file\n");
    }

    return 0;
}