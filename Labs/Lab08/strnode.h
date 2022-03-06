/* Katy Martinson
 * Lab 08
 * Tuesday 1pm
 * strnode.h
 */

#ifndef STRNODE_H_
#define STRNODE_H_
#include <stdio.h>

struct strnode {
  char* str;
  int length; 
  struct strnode* next;
};

struct strnode *strnode_create(char *s, int length);

#endif    //STRNODE
