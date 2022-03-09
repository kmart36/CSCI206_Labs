/* Katy Martinson
 * Lab 08
 * Tuesday 1pm
 * strnode.c
 */

#include "node.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node *node_create(void *data, int size) {
  struct node * one_node = (struct node *)malloc(sizeof(struct node));
  one_node->data = (void*)malloc(size + 1);
  memcpy(one_node->data, data, size);
  one_node->length = size;
  one_node->next = NULL;
  return one_node;
} 

void node_destroy(struct node *n) {
  free(n->data);
  free(n);
}
