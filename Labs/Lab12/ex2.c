/* ex2.c SHIFTs test */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

int main(int argc, char* argv[]){
  struct bigint *a = bigint_init("1101", 8);  // 13
  char a_str[16];
  char b_str[16];
  char c_str[16];

  bigint_str(a_str, a);

  bigint_lshift(a, 3);     // 13 << 3 == 13 x 8 == 104
  bigint_str(b_str, a);

  bigint_rshift(a, 2);     // 104 >> 2 == 104 / 4 == 26
  bigint_str(c_str, a);

  printf("SHFITS test\n");
  printf("%s\n", a_str);
  printf("%s << 3 == %s\n", a_str, b_str);
  printf("%s >> 2 == %s\n", a_str, c_str);

  free(a);

  return 0;
}
