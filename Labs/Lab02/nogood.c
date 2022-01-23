/* Katy Martinson
 * nogood.c -- a program with errors
 * Stephen Prata - C Primer Plus 6/e - Listing 2.4
 * compile with: $ make nogood.c 
 */
#include <stdio.h>

int main(void)
{
   int n, n2, n3;
 
   // This program has no more errors :)
   n = 5;
   n2 = n * n;
   n3 = n2 * n;
 
   printf("n = %d, n squared = %d, n cubed = %d\n", n, n2, n3);
 
   return 0;
}
