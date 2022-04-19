#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

int main(){
    int size = 0;
    struct pair *map = createMap(5);
    mapAdd(map, "a", 1, size);
    size++;
    mapAdd(map, "b", 2, size);
    size++;
    mapAdd(map, "c", 3, size);
    size++;

    for(char i = 0; i < (char)size; i++){
        printf("%s\n", pairString(map[(int)i]));
        char str[3];
        str[(int)i] = i + 'a';
        printf("mapGetValue(%s) = %d\n", str, mapGetValue(map, str, size)); 
    }
    return 1;
}