CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@ -lm

compile : compile.c match_braces.c
	$(CC) -g -Wall -Wvla -Werror compile.c match_braces.c -o $@
