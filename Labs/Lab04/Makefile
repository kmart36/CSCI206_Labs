CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
SRC=better_dictionary.c speller.c
OBJF=better_dictionary.o speller.o            # objects needed for fsm
EXE=speller                        # executables

all: $(EXE)

%.o:%.c dictionary.h
	$(CC) $(CFLAGS) -c $< -o $@

speller: speller.o better_dictionary.o
	$(CC) -o $@ speller.o better_dictionary.o

clean: 
	/bin/rm -f *.o *~ $(EXE)
