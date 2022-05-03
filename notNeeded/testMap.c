#include <stdio.h>
#include <stdlib.h>
#include "Map.h"

int main(){
    int size = 5;
    struct pair *map = createMap(size);

    mapAdd(map, "hello", 15, size);
    mapAdd(map, "wonder", 100, size);
    mapAdd(map, "abcd", -3, size);

    printf("mapGetValue(%s) = %d\n", "hello", mapGetValue(map, "hello", size)); 
    printf("mapGetValue(%s) = %d\n", "wonder", mapGetValue(map, "wonder", size));
    printf("mapGetValue(%s) = %d\n", "abcd", mapGetValue(map, "abcd", size));
    printf("mapGetValue(%s) = %d\n", "doesn't exist", mapGetValue(map, "doesn't exist", size));
    printf("\nSymbol Table:\n%s", mapToString(map, size));
    return 1;
}