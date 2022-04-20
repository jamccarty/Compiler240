#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Map.h"

struct pair* createMap(const int size){
    struct pair* map = malloc(sizeof(struct pair) * size);
    if(map == NULL){
        printf("ERROR: map allocation failed for map size %d\n", size);
        exit(1);
    }
    return map;
}

void mapAdd(struct pair *map, char* key, int value, const int size){
    int len = strlen(key);
    int hash = 0;
    for(int i = 0; i < len; i++){
        hash = hash + (int)(key[i]);
    }
    hash = hash % size;
    while(map[hash].key != NULL){
        hash++;
        if(hash == size){
            hash = 0;
        }
    }
    map[hash].key = key;
    map[hash].key = key;
}

int mapGetValue(struct pair* map, char* key, const int size){
    int len = strlen(key);
    int hash = 0;
    for(int i = 0; i < len; i++){
        hash = hash + (int)(key[i]);
    }
    hash = hash % size;
    if(map[hash].key == NULL){
        return 0;
    }
    while(strcmp(map[hash].key, key) != 0){
        hash++;
        if(map[hash].key == NULL){
            return 0;
        }
        if(hash == size){
            hash = 0;
        }
    }
    return map[hash].value;
}

char *pairString(struct pair p){
    char *ret = malloc(sizeof(char) * 50);
    memset(ret, '\0', 50);
    sprintf(ret, "(%s, %d)", p.key, p.value);
    return ret;
}

