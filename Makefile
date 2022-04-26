CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@ -lm

testMap: testMap.c Map.c
	$(CC) -g -Wall -Wvla -Werror testMap.c Map.c -o $@ -lm

CreateSymbolTable: CreateSymbolTable.c Map.c
	$(CC) -g -Wall -Wvla -Werror CreateSymbolTable.c Map.c -o $@ -lm

compile: compile.c Map.c
	$(CC) -g -Wall -Wvla -Werror compile.c Map.c -o $@ -lm