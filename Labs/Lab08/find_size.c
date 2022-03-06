/* Katy Martinson
 * Lab 08
 * Tuesday 1pm
 * find_size.c
 */

#include <stdio.h>


struct course_t {
  int  ID;           
  int  enrollment;   
  char title[32];    
  char prof[32];     
};

struct course_node_t {
  int                 ID;
  int                 enrollment;
  char*               title;
  char*               prof;
  struct course_node_t*    next;
};

int main(void) {
  printf("%i\n", (int)sizeof(struct course_t));
  printf("%i\n", (int)sizeof(struct course_node_t));
}
