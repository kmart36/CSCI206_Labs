/* Katy Martinson
 * Tuesday - 1pm
 * lab 02 - isalary.c
 * compile with: $ make isalary
 * notes: none
 */

#include <stdio.h>
 
int main(void) 
{
  int hourly_wage;
  printf("Enter hourly wage (integer): ");
  scanf("%i", &hourly_wage);
 
  printf("Annual salary is: ");
  printf("%d", hourly_wage * 40 * 50);
  printf("\n");
 
  return 0;
}
