
CC = cc
CFLAGS = -Wall -Werror -std=gnu99

# librt is needed for clock_gettime
LDLIBS = -lrt -lm

targets = parse dm_cache_sim cache_sim benchmark-naive benchmark-blocked 
objects = benchmark.o dgemm-naive.o dgemm-blocked.o

.PHONY : default
default : all

.PHONY : all
all : clean $(targets)

benchmark-naive : benchmark.o dgemm-naive.o
	$(CC) -o $@ $^ $(LDLIBS)
benchmark-blocked : benchmark.o dgemm-blocked.o
	$(CC) -o $@ $^ $(LDLIBS)

# math.h uses the math library, so link it on
cache_sim: cache_sim.o

dm_cache_sim: dm_cache_sim.o



.PHONY : clean
clean:
	rm -f $(targets) $(objects) *~ *.o
