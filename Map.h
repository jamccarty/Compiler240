#ifndef MAP_H_
#define MAP_H_

struct pair {
    char key[100];
    int value;
};

extern struct pair* createMap(int size);
extern void mapAdd(struct pair* map, char* key, int value, const int size);
extern int mapGetValue(struct pair* map, char* key, const int size);
extern char *mapToString(struct pair *map, int size);
extern void closeMap(struct pair *map, int size);

#endif