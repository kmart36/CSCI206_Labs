CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
SRC=sha_sum.c sha256.c
OBJF=sha_sum.o sha256.o            # objects needed for fsm
EXE=sha_sum                        # executables

all: $(EXE)

%.o:%.c sha256.h
	$(CC) $(CFLAGS) -c $< -o $@

sha_sum: sha_sum.o sha256.o
	$(CC) -o $@ sha_sum.o sha256.o

clean: 
	/bin/rm -f *.o *~ $(EXE)
