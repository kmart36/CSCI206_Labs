CC = gcc
AS = as
CFLAGS = -std=c99 -Wall -Werror -g

%.o: %.c
	$(CC) -c $< -o $@

double: double.c double-riscv.s
	$(CC) $(CFLAGS) $^ -o $@

counte: counte.c counte.s
	$(CC) $(CFLAGS) $^ -o $@

time: time.c time.s
	$(CC) $(CFLAGS) $^ -o $@

list_primes: list_primes.c is_prime.s
	$(CC) $(CFLAGS) $^ -o $@

check_primes: check_primes.c check_primes.s
	$(CC) $(CFLAGS) $^ -o $@

clean:
		rm -rf *.o *~ $(EXE)
