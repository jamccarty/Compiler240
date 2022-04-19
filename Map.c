#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

struct pair* createMap(int size){
    struct pair* map = malloc(sizeof(struct pair) * size);
    if(map == NULL){
        printf("ERROR: map allocation failed for map size %d\n", size);
        exit(1);
    }
    return map;
}

void mapAdd(struct pair *map, char* key, int value, int filled_size){
    map[filled_size].key = key;
    map[filled_size].value = value;
}

int mapGetValue(struct pair* map, char* key, int filled_size){
    for(int i = 0; i < filled_size; i++){
        if(strcmp(map[i].key, key) == 0){
            return map[i].value;
        }
    }
    return 0;
}

char *pairString(struct pair p){
    char *ret = malloc(sizeof(char) * 50);
    memset(ret, '\0', 50);
    sprintf(ret, "(%s, %d)", p.key, p.value);
    return ret;
}

