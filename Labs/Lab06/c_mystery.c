/* Katy Martinson
 * Lab 06
 * Section 61 - Tuesday 1pm
 * c_mystery.c
 * Notes: make c_mystery
 */

#include <stdio.h>

int unused = 0xFEEDBEEF;
int x = 89;

int main() {
  int count = 0;
  int sum = 0;
  int breaker;
  
  do {
	sum += count;
	count++;
	breaker = count - 10;
  } while (breaker <= 0);
  
  x = sum;
  printf("%i", x);
  printf("%i", unused);
  return x;
}
