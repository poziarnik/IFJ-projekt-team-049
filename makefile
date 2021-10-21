CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -lm -fcommon -g
FILES = Scanner.c Scanner.h main.c
NEWFILE = test

advanced: 
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) 

primitive:
	$(CC) -std=c99 -o $(NEWFILE) $(FILES) 

	