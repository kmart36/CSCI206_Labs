CC=gcc
CFLAGS=-Wall -Wfatal-errors -Werror -std=c99
LDLIBS=-lm
all: strnode_test
node_test: node.o node_test.o node.h
strnode_test: strnode.o strnode_test.o strnode.h
stack_test: node.o node.h stack.o stack_test.o stack.h
pcalc: node.o node.h stack.o stack.h pcalc.o
clean:
	rm -f strnode_test *.o
