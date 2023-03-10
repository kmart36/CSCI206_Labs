/* Katy Martinson
 * Tuesday - 1pm
 * lab 02 - fsalary.c
 * compile with: $ make fsalary
 * notes: none
 */

#include <stdio.h>
 
int main(void) 
{
  float hourly_wage;
  printf("Enter hourly wage (float): ");
  scanf("%f", &hourly_wage);
  
  int weeks_worked;
  printf("Enter weeks worked (integer): ");
  scanf("%i", &weeks_worked);

  printf("Annual salary is: $");
  printf("%.2f", hourly_wage * 40 * weeks_worked);
  printf("\n");
 
  return 0;
}

