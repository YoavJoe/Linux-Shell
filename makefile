# All Targets
BIN=./bin/
SOURCE=./src/
INCLUDE=./include/

CFLAGS=-g -Wall -ansi -pedantic -c
C=-g -Wall -o

all: myShell

myShell: linklist.o lineparser.o myshell.o main.o
	@gcc $(C) myShell $(BIN)/linklist.o $(BIN)/lineparser.o $(BIN)/myshell.o $(BIN)/main.o

main.o: $(SOURCE)/main.c
	@gcc $(CFLAGS) $(SOURCE)/main.c -o $(BIN)/main.o

myshell.o: $(SOURCE)/myshell.c $(INCLUDE)/myshell.h
	@gcc $(CFLAGS) $(SOURCE)/myshell.c -o $(BIN)/myshell.o

lineparser.o: $(SOURCE)/LineParser.c $(INCLUDE)/LineParser.h
	@gcc $(CFLAGS) $(SOURCE)/LineParser.c -o $(BIN)/lineparser.o

linklist.o: $(SOURCE)/linklist.c $(INCLUDE)/linklist.h
	@mkdir -p bin
	@gcc $(CFLAGS) $(SOURCE)/linklist.c -o $(BIN)/linklist.o	

#tell make that "clean" is not a file name!
.PHONY: clean run debug

clean:
	@rm -vf $(BIN)/* myShell

run: myShell
	./myShell

debug: myShell
	@gdb myShell

memcheck: myShell
	valgrind --leak-check=yes ./myShell
