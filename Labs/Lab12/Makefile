CFLAGS = -Wall -g -Wfatal-errors -std=c99
CC     = gcc
EXE    = ex1 ex2 ex3 ex4 ex5
all: $(EXE)
ex1: bigint.o ex1.o
ex2: bigint.o ex2.o
ex3: bigint.o ex3.o
ex4: bigint.o ex4.o
ex5: bigint.o ex5.o

clean:
	/bin/rm -f core *.o $(EXE) *~
