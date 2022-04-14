CC=gcc
% :: %.c
	$(CC) -g -Wall -Wvla -Werror $< -o $@ -lm

compile : compile.c match_braces.c
	$(CC) -g -Wall -Wvla -Werror compile.c match_braces.c -o $@

ParseFunctionHeader : ParseFunctionHeader.c match_braces.c
	$(CC) -g -Wall -Wvla -Werror ParseFunctionHeader.c match_braces.c -o $@

ReturnVarArray : ReturnVarArray.c ParseFunctionHeader.c
	$(CC) -g -Wall -Wvla -Werror ReturnVarArray.c ParseFunctionHeader.c -o $@

parse_test : parse_test.c ParseFunctionHeader.c
	$(CC) -g -Wall -Wvla -Werror parse_test.c ParseFunctionHeader.c -o $@
