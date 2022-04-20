CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@ -lm

testMap: testMap.c Map.c
	$(CC) -g -Wall -Wvla -Werror testMap.c Map.c -o $@ -lm
