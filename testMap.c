#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

int main(){
    int size = 5;
    struct pair *map = createMap(size);
    mapAdd(map, "a", 1, size);
    mapAdd(map, "b", 2, size);
    mapAdd(map, "c", 3, size);

    for(char i = 0; i < (char)size; i++){
        printf("%s\n", pairString(map[(int)i]));
        char a = i + 'a';
        char str[3];
        str[0] = a;
        str[1] = '\0';
        printf("mapGetValue(%s) = %d\n", str, mapGetValue(map, str, size)); 
    }
    return 1;
}