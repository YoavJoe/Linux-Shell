# All Targets
BIN=./bin/
SOURCE=./src/
INCLUDE=./include/

CFLAGS=-g -Wall -ansi -pedantic -c
C=-g -Wall -o

all: myShell

myShell: utils.o pipeline.o linklist.o lineparser.o myshell.o
	@gcc $(C) myShell $(BIN)utils.o $(BIN)pipeline.o $(BIN)/linklist.o $(BIN)/lineparser.o $(BIN)/myshell.o

myshell.o: $(SOURCE)/myshell.c $(INCLUDE)/myshell.h
	@gcc $(CFLAGS) $(SOURCE)/myshell.c -o $(BIN)/myshell.o

lineparser.o: $(SOURCE)/LineParser.c $(INCLUDE)/LineParser.h
	@gcc $(CFLAGS) $(SOURCE)/LineParser.c -o $(BIN)/lineparser.o

linklist.o: $(SOURCE)/linklist.c $(INCLUDE)/linklist.h
	@gcc $(CFLAGS) $(SOURCE)/linklist.c -o $(BIN)/linklist.o

pipeline.o: $(SOURCE)/pipeline.c $(INCLUDE)/pipeline.h
	@gcc $(CFLAGS) $(SOURCE)/pipeline.c -o $(BIN)/pipeline.o

utils.o: $(SOURCE)/utils.c $(INCLUDE)/utils.h
	@mkdir -p bin
	@gcc $(CFLAGS) $(SOURCE)/utils.c -o $(BIN)/utils.o

#tell make that "clean" is not a file name!
.PHONY: clean run debug

clean:
	@rm -vf $(BIN)/* myShell

run: myShell
	@./myShell

debug: myShell
	@gdb myShell

memcheck: myShell
	valgrind --leak-check=yes ./myShell
