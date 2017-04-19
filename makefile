OBJS = integer.o real.o str.o sll.o dll.o stack.o queue.o bst.o vbst.o rbt.o comparator.o scanner.o bstrees.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all : bstrees

bstrees : $(OBJS)
	gcc $(LOPTS) -o bstrees $(OBJS)

comparator.o : comparator.c comparator.h
	gcc $(OOPTS) comparator.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c
	
sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h
	gcc $(OOPTS) queue.c

bst.o: bst.c bst.h
	gcc $(OOPTS) bst.c

vbst.o: vbst.c vbst.h
	gcc $(OOPTS) vbst.c

rbt.o: rbt.c rbt.h
	gcc $(OOPTS) rbt.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

str.o : str.c str.h
	gcc $(OOPTS) str.c

bstrees.o : bstrees.c integer.h real.h str.h sll.h dll.h stack.h queue.h bst.h vbst.h rbt.h comparator.h scanner.h
	gcc $(OOPTS) bstrees.c

make test : bstrees
	./bstrees -v corpus commands

clean :
	rm -f $(OBJS) bstrees