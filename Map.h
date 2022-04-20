#ifndef MAP_H_
#define MAP_H_

struct pair {
    char* key;
    int value;
};

extern struct pair* createMap(int size);
extern void mapAdd(struct pair* map, char* key, int value, const int size);
extern int mapGetValue(struct pair* map, char* key, const int size);
extern char *pairString(struct pair p);

#endif

