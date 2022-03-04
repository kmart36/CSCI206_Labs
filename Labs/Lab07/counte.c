/* Katy Martinson
 * 3/1/22
 * Tuesday - 1pm
 * counte.c
 */

#include <stdio.h>
#define MAX 80

extern int counte(char *);

int main(void) {
  char line[MAX];
  int count = 0;

  printf("Enter a string: ");
  fgets(line, MAX - 1, stdin);
  count = counte(line);
  printf("There are %d e's\n", count);

  return 0;
}
