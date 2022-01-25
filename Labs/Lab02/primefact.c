/* Katy Martinson
   Tuesday 1/25/22
   Section 61
   Compile with: $ make primefact
   Notes: C is 56.7 times faster than Python
   C time: 0.04s
   Python time: 2.268s
 */
#include <stdio.h>

int main(void) {
  int n = 2147483645;
  int i = 2;
  while (i <= n) {
	if (n % i == 0) { 
	  printf("%i\n", i);
	  n = n / i;
	}
	else 
	  i++;
  }
  return 0;
}
