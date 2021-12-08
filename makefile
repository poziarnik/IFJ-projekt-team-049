CC = gcc
CFLAGS = -std=c99 -Wall -pedantic -lm -fcommon -g
FILES = Scanner.c Scanner.h Mystack.c MyStackTree.h Parser.c Parser.h ParserDownUp.c ParserDownUp.h symtable.c symtable.h AST.c AST.h generator.c generator.h
MAIN =testParserMain.c
NEWFILE = test
PRECEDENCE = Scanner.c Scanner.h Mystack.c MyStackTree.h ParserDownUp.c ParserDownUp.h symtable.c symtable.h 
SCANNER = Scanner.c Scanner.h

all:
	$(CC) -std=c99 -o $(NEWFILE) $(FILES) Main.c
