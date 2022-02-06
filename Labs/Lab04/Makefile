CC=gcc
CFLAGS=-std=c99 -Wall -Werror -g
SRC=fsm.c tokens.c
OBJF=fsm.o tokens.o            # objects needed for fsm
EXE=fsm                        # executables

all: $(EXE)

%.o:%.c tokens.h
	$(CC) $(CFLAGS) -c $< -o $@

fsm: fsm.o tokens.o
	$(CC) -o $@ fsm.o tokens.o

clean: 
	/bin/rm -f *.o *~ $(EXE)
