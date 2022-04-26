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
    for(int i = 0; i < size; i++){
        strcpy(map[i].key, "");
    }
    return map;
}

void mapAdd(struct pair *map, char* key, int value, const int size){
    int len = strlen(key);
    int hash = 0;
    int count = 0;
    for(int i = 0; i < len; i++){
        hash = hash + (int)(key[i]);
    }
    hash = hash % size;
    while(strcmp(map[hash].key, "") != 0){
        hash++;
        count++;
        if(count == size){
            printf("ERROR: not enough space to add new pair (%s, %d)\n", key, value);
            exit(1);
        }
        if(hash == size){
            hash = 0;
        }
    }
    strcpy(map[hash].key, key);
    map[hash].value = value;
}

int mapGetValue(struct pair* map, char* key, const int size){
    int len = strlen(key);
    int hash = 0;
    for(int i = 0; i < len; i++){
        hash = hash + (int)(key[i]);
    }
    hash = hash % size;
    if(strcmp(map[hash].key, "") == 0){
        return 1;
    }
    while(strcmp(map[hash].key, key) != 0){
        hash++;
        if(strcmp(map[hash].key, "") == 0){
            return 1;
        }
        if(hash == size){
            hash = 0;
        }
    }
    return map[hash].value;
}

char *mapToString(struct pair *map, int size){
    char *ret = malloc(sizeof(char) * 50 * size);
    ret[0] = '\0';
    char *add = malloc(sizeof(char) * 50);
    add[0] = '\0';
    for(int i = 0; i < size; i++){
        if(strcmp(map[i].key, "") != 0){
            memset(add, '\0', 50);
            sprintf(add, "%s %d\n", map[i].key, map[i].value);
            strcat(ret, add);
        }
    }
    free(add);
    add = NULL;
    return ret;
}

void closeMap(struct pair *map, int size){
    free(map);
    map = NULL;
}