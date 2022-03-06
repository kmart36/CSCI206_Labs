/*
 * check_primes.c
 */
#include <stdio.h> 
#include <stdlib.h>


void check_primes(int a, int b, int *r);


int main (int argc, char* argv[])
{
   if (argc != 3) {
	  printf("Usage: %s a count\n", argv[0]);
	  printf("Where a is the starting int (a > 0), count is how many.\n");
	  exit(1);
   }

   int left = atoi(argv[1]);
   int right = left + atoi(argv[2]);
   int count = right - left + 1;  // how many
   int *result = (int *)malloc(count * sizeof(int));
   int i;

   printf("left = %d right = %d\n", left, right);
   check_primes(left, right, result);
	
    for (i = left; i < right; i++){
	   printf("%7d %7s a prime\n", i,
			  (result[i - left] == 1) ? "is ": "isn't ");
	}

    return 0;
}
