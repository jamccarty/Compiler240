#ifndef MAP_H_
#define MAP_H_

struct pair {
    char* key;
    int value;
};

extern struct pair* createMap(int size);
extern void mapAdd(struct pair* map, char* key, int value, int filled_size);
extern int mapGetValue(struct pair* map, char* key, int filled_size);
extern char *pairString(struct pair p);

#endif

