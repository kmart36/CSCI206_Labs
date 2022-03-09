/* Katy Martinson
 * Lab 08
 * Tuesday 1pm
 * strnode.h
 */

#ifndef NODE_H_
#define NODE_H_
#include <stdio.h>

struct node {
  void* data;
  int length; 
  struct node* next;
};

struct node *node_create(void *data, int size);

void node_destroy(struct node *n);

#endif    //NODE
