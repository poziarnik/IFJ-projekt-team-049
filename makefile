CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -lm -fcommon -g
FILES = Scanner.c Scanner.h main.c

run: 
	$(CC) $(CFLAGS) -o test $(FILES) 

primitive:
	$(CC) -std=c99 -o test $(FILES) 
