/* Katy Martinson
 * CSCI 206 - 61
 * Tuesday 1pm
 * pcalc.c
 */

#include <ctype.h>
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int is_operator(char);

int main(int argc, char *argv[]) {
  float result, operand1, operand2;
  struct stack* stack = stack_create();
  for (int i = 1; i < argc; i++) {
	if (is_operator(argv[i][0]) == 1) {
	  stack_pop(stack, &operand2, sizeof(float));
	  stack_pop(stack, &operand1, sizeof(float));
	  if (argv[i][0] == '+')
		result = operand1 + operand2;
	  else if (argv[i][0] == '-')
		result = operand1 - operand2;
	  else if (argv[i][0] == 'x')
		result = operand1 * operand2;
	  else if (argv[i][0] == '/')
		result = operand1 / operand2;
	  else if (argv[i][0] == '^')
		result = pow(operand1, operand2);
	  stack_push(stack, &result, sizeof(float));
	}
	else {
	  float op = atof(argv[i]);
	  stack_push(stack, &op, sizeof(float));
	}
  }
  while(!stack_isempty(stack)) {
	stack_pop(stack, &result, sizeof(float));
	printf("%f\n", result);
  }
  stack_destroy(stack);
}

int is_operator(char token) {
  if (token == '+' || token == '-' || token == 'x' || token == '/' || token == '^')
	return 1;
  return 0;
}
