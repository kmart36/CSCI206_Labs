CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
SRC=dictionary.c speller.c
OBJF=dictionary.o speller.o            # objects needed for fsm
EXE=speller                        # executables

all: $(EXE)

%.o:%.c sha256.h
	$(CC) $(CFLAGS) -c $< -o $@

speller: speller.o dictionary.o
	$(CC) -o $@ speller.o dictionary.o

clean: 
	/bin/rm -f *.o *~ $(EXE)
