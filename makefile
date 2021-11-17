CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -lm -fcommon -g
FILES = Scanner.c Scanner.h stack.c stack.h Parser.c Parser.h ParserDownUp.c ParserDownUp.h 
MAIN =testParserMain.c
#testParserMain.c - parsovanie
#main.c - scanner
#testMain.c - zdolaNahor
NEWFILE = test

advanced: 
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) $(MAIN)

primitive:
	$(CC) -std=c99 	-o $(NEWFILE) $(FILES) $(MAIN)

scanner:
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) main.c

parser:
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) testParserMain.c
	