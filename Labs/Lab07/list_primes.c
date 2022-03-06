/*
 * list_primes.c
 */
#include <stdio.h> 
#include <stdlib.h>

extern int is_prime(int n);  // prototype

int main (int argc, char* argv[])
{
    int i, n = 0, maxnum = 80;
    if (argc > 1){
        maxnum = atoi(argv[1]);
    }
    for (i = 2; n < maxnum; i++){
	   printf("%7d %7s a prime\n", i,
			  (is_prime(i) == 1) ? "is ": "isn't ");
	   n++;
	}

    return 0;
}

