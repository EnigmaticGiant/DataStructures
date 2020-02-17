OBJS = trees.o cda.o queue.o string.o gst.o rbt.o bst.o scanner.o real.o integer.o tnode.o 
OPTS = gcc -Wall -Wextra -g -std=c99

all: trees

trees: trees.o tnode.o scanner.o cda.o queue.o string.o gst.o string.o real.o integer.o rbt.o bst.o
	$(OPTS) -o trees trees.o tnode.o scanner.o gst.o cda.o rbt.o queue.o bst.o string.o real.o integer.o

bst.o: bst.h bst.c tnode.c
	$(OPTS) -c bst.c

cda.o: cda.h integer.h cda.c queue.c
	$(OPTS) -c cda.c

gst.o: gst.h gst.c bst.h bst.c tnode.c
	$(OPTS) -c gst.c

tnode.o: tnode.c tnode.h
	$(OPTS) -c tnode.c

queue.o: queue.h queue.c cda.c cda.h
	$(OPTS) -c queue.c

trees.o: trees.c tnode.c scanner.c scanner.h cda.h queue.c queue.h string.c string.h bst.c bst.h gst.c gst.h rbt.c rbt.h
	$(OPTS) -c trees.c

rbt.o: tnode.c tnode.h rbt.h rbt.c gst.c gst.h string.h string.c 
	$(OPTS) -c rbt.c

integer.o: integer.h integer.c
	$(OPTS) -c integer.c

real.o: real.h real.c
	$(OPTS) -c real.c

string.o:	string.h string.c
	$(OPTS) -c string.c

scanner.o: scanner.h scanner.c
	$(OPTS) -c scanner.c

clean: 
	rm -f *.o trees

valgrind:
	valgrind --leak-check=full trees -g corpus commands
	
test:
	gcc -Wall -g -Wextra trees.c tnode.c gst.c bst.c integer.c string.c real.c cda.c queue.c rbt.c string.c scanner.c
	trees -g t-0-7.corpus t-0-7.commands

