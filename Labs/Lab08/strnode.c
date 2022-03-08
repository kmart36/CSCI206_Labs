/* Katy Martinson
 * Lab 08
 * Tuesday 1pm
 * strnode.c
 */

#include "strnode.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct strnode *strnode_create(char *s, int length) {
  struct strnode * one_str_node = (struct strnode *)malloc(sizeof(struct strnode));
  one_str_node->str = (char*)malloc(strlen(s) + 1);
  strcpy(one_str_node->str, s);
  one_str_node->length = strlen(one_str_node->str) + 1;
  one_str_node->next = NULL;
  return one_str_node;
} 
