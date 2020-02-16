OBJS = da.o cda.o stack.o queue.o
OPTS = gcc -Wall -Wextra -g -std=c99 -ggdb3

all: testDA testCDA testSTACK testQUEUE

testDA: testDA.o integer.o da.o
	$(OPTS) -o testDA testDA.o integer.o da.o

testCDA: testCDA.o integer.o cda.o
	$(OPTS) -o testCDA testCDA.o integer.o cda.o

testSTACK: testSTACK.o integer.o da.o stack.o
	$(OPTS) -o testSTACK testSTACK.o integer.o da.o stack.o

testQUEUE: testQUEUE.o integer.o cda.o queue.o
	$(OPTS) -o testQUEUE testQUEUE.o integer.o queue.o cda.o

da.o: da.h da.c
	$(OPTS) -c da.c

cda.o: cda.h cda.c
	$(OPTS) -c cda.c

stack.o: stack.h da.h stack.c
	$(OPTS) -c stack.c

queue.o: queue.h cda.h queue.c
	$(OPTS) -c queue.c

testDA.o: integer.h da.h testDA.c
	$(OPTS) -c testDA.c

testCDA.o: integer.h cda.h testCDA.c
	$(OPTS) -c testCDA.c

testSTACK.o: integer.h stack.h da.h testSTACK.c
	$(OPTS) -c testSTACK.c

testQUEUE.o: integer.h queue.h cda.h testQUEUE.c
	$(OPTS) -c testQUEUE.c

integer.o: integer.h integer.c
	$(OPTS) -c integer.c

clean: 
	rm -f *.o testDA
	rm -f *.o testCDA
	rm -f *.o testSTACK
	rm -f *.o testQUEUE

valgrind:
	valgrind testDA
	valgrind testCDA
	valgrind testSTACK
	valgrind testQUEUE

test:
	gcc -Wall -Wextra -g -std=c99 cda-2-3.c cda.c cda.h integer.c -o mytest
	valgrind ./mytest