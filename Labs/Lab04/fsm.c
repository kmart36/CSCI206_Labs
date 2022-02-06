/* Katy Martinson
 * Tuesday 1pm
 * Section 61
 * File name: fsm.c
 * Compile with: gcc -std=c99 -Wall -Werror -g fsm.c tokens.c -o fsm
 *
 * This file contains a few finite state machines that recognize various
 * patterns.
 *
 * CSCI 206 exercises (student file)
 */
#include "tokens.h"

const int MAX_LENGTH = 16;

int main(int argc, char *argv[]) {

  if (argc != 2) {
	fprintf(stderr, "Usage: %s string\n", argv[0]);
	exit(1);
  }

  //parse_int(argv[1]);
  parse_word(argv[1]);

  return 0;
}
