/* Katy Martinson
 * CSCI 206
 * Tuesday 1pm
 * stack.c
 */

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack *stack_create() {
  struct stack *my_stack = (struct stack*)malloc(sizeof(struct stack));
  my_stack->top = NULL;
  return my_stack;
}

int stack_isempty(struct stack *s) {
  if (s->top == NULL)
	return 1;
  return 0;
}

void stack_destroy(struct stack *s) {
  float f = 1.0;
  while(!stack_isempty(s)) {
	stack_pop(s, &f, s->top->length);
  }
  free(s);
}

void stack_push(struct stack *s, void *src, int size) {
  struct node *new_node = node_create(src, size);
  new_node->next = s->top;
  s->top = new_node;
}

void stack_pop(struct stack *s, void *dest, int size) {
  struct node *old_top = s->top;
  s->top = old_top->next;
  memcpy(dest, old_top->data, size);
  node_destroy(old_top);
}
