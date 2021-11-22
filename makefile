CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -lm -fcommon -g
FILES = Scanner.c Scanner.h Mystack.c MyStackTree.h Parser.c Parser.h ParserDownUp.c ParserDownUp.h 
MAIN =testParserMain.c
NEWFILE = test
PRECEDENCE = Scanner.c Scanner.h Mystack.c MyStackTree.h ParserDownUp.c ParserDownUp.h 

advanced: 
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) $(MAIN)

primitive:
	$(CC) -std=c99 	-o $(NEWFILE) $(FILES) $(MAIN)

scanner:
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) main.c

parser:
	$(CC) -std=c99 -o $(NEWFILE) $(FILES) testParserMain.c
	
precedence:
	$(CC) -std=c99 -o $(NEWFILE) $(PRECEDENCE) testMain.c
