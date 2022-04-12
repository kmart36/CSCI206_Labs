#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "bigint.h"

/*
 * Create an initalize a new bigint structure
 *
 * struct bigint {
 *   int N;
 *   char digit[];
 * };
 * 
 */
struct bigint* bigint_init(char* value, int N){
  int i;
  int k = strlen(value);
  struct bigint* r;

  // ensure N is divisible by 4
  if (N%4 > 0){
    N += (4-(N%4));
  }

  if (k > N){
    printf("ERROR: too many digits\n");
    exit(1);
  }

  r = malloc(sizeof(struct bigint) + N);
  r->N = N;
  bigint_zero(r);

  // copy digits from the C string value into the digits
  for(i = 0; i < k; i++){
    r->digit[i] = value[k - i - 1];
  }
  return r;
}

/*
 * set every digit to 0
 */
void bigint_zero(struct bigint* bn){
  memset(bn->digit, '0', bn->N);
}

/*
 * Copy the binary digit string into dst.
 */
void bigint_str(char* dst, struct bigint* bn){
  int i;
  for(i = bn->N; i > 0; i--){
    *dst++ = bn->digit[i-1];
    if ( (i-1)%4 == 0){
      *dst++ = ' ';
    }
  }
  *dst = '\0';
}

/*
 * todo, incomplete [optional?]
 */
void bigint_hexstr(char* dst, struct bigint* bn){
  *dst= '\0';
}

/* 
 * a standard full adder.
 * this might be useful.
 */
void full_add(char carry_in, char a, char b, char* sum, char* carry_out){
  int i =0;
  if (a == '1') i++;
  if (b == '1') i++;
  if (carry_in == '1') i++;
  switch(i){
    case 0: *sum = '0'; *carry_out = '0'; break;
    case 1: *sum = '1'; *carry_out = '0'; break;
    case 2: *sum = '0'; *carry_out = '1'; break;
    case 3: *sum = '1'; *carry_out = '1'; break;
    default: printf("Impossible error!\n"); exit(255);
  }
}

/*
 * c = a + b
 */
void bigint_add(struct bigint* c, struct bigint* a, struct bigint* b){
}

/*
 * out = -in
 */
void bigint_inv(struct bigint* out, struct bigint* in){
}

/*
 * c = a - b
 */
void bigint_sub(struct bigint* c, struct bigint* a, struct bigint* b){
}

/*
 * Right shift the bigint, in place by *bits*
 */
void bigint_lshift(struct bigint *bn, int bits){
	int i = bn->N - 1;
	while (bn->digit[i] != '1') {
		i--;
	}
	for (int j = i; j >= 0; j--) {
		bn->digit[j + bits] = bn->digit[j];
	}
	for (int m = 0; m < bits; m++) {
		bn->digit[m] = '0';
	}
}

/*
 * Left shift the bigint, in place by *bits*
 */
void bigint_rshift(struct bigint *bn, int bits){
	int i = bn->N - 1;
	while (bn->digit[i] != '1') {
		i--;
	}
	for (int j = 0; j <= i; j++) {
		bn->digit[j] = bn->digit[j + bits];
	}
	for (int m = bn->N - 1; m >= bn->N - 1 - bits; m--) {
	  bn->digit[m] = '0';
	}
}

/*
 * prod = mcand * mplier
 */
void bigint_mult(
  struct bigint* prod,
  struct bigint* mcand,
  struct bigint* mplier){
}

/*
 * quotient = dividend / divisor
 * remainder = dividend % divisor
 */
void bigint_div(
  struct bigint* quotient,
  struct bigint* remainder,
  struct bigint* dividend,
  struct bigint* divisor){

}

/*
 * return zero if *in* is zero, else 1
 */
int bigint_iszero(struct bigint* in){
  return 1;
}

/* 
 * return a new copy of *in* 
 */
struct bigint* bigint_copy(struct bigint* in){
    return NULL;
}

/*
 * result = in! (factorial)
 */
void bigint_fact(
  struct bigint* result,
  struct bigint* in){
}
