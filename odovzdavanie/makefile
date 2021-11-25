CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -lm -fcommon -g
FILES = Scanner.c Scanner.h Mystack.c MyStackTree.h Parser.c Parser.h ParserDownUp.c ParserDownUp.h symtable.c symtable.h 
MAIN =testParserMain.c
NEWFILE = test
PRECEDENCE = Scanner.c Scanner.h Mystack.c MyStackTree.h ParserDownUp.c ParserDownUp.h symtable.c symtable.h 

all:
	$(CC) $(CFLAGS) -o $(NEWFILE) $(FILES) MainMain.c

.PHONY: pack
pack:
	tar -vcf xhatal01.tgz *.c *.h makefile
