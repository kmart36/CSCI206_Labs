/* Katy Martinson
 * Tuesday - 1pm
 * Section 61
 * File: calc.c
 * Compile: $ make calc
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isvalid(char * s);
bool isinteger(char * s);
bool my_isdigit(char c); 

int main(int argc, char * argv[]) {
  if (argc < 3) {
	printf("More arguments are needed\n");
	exit(1);
  }
  else {
	if (!isvalid(argv[1])) {
	  printf("Unsupported function, try: add, mult, div, or len\n");
	  exit(1);
	}
	else {
	  if (strcmp(argv[1], "len") == 0) {
		int total = 0;
		for (int i = 2; i < argc; i++) { 
		  total += (int)strlen(argv[i]);
		}
		printf("%i\n", total);
	  }
	  else if (argc < 4) {
		printf("More arguments are needed\n");
		exit(1);
	  }
	  else if (strcmp(argv[1], "add") == 0) {
		int sum = 0;
		for (int i = 2; i < argc; i++) {
		  if (!isinteger(argv[i])) {
			printf("Invalid operands\n");
			exit(1);
		  }
		  sum += atoi(argv[i]);
		}
		printf("%i\n", sum);
	  }
	  else if (strcmp(argv[1], "mult") == 0) {
		int multi = 1; 
		for (int i = 2; i < argc; i++) {
		  if (!isinteger(argv[i])) {
			printf("Invalid operands\n");
			exit(1);
		  }
		  multi = multi * atoi(argv[i]);
		}
		printf("%i\n", multi);
	  }
	  else {
		int divide = 1;
		for (int i = 2; i < argc; i++) {
		  if (!isinteger(argv[i])) {
			printf("Invalid operands\n");
			exit(1);
		  }
		  if (i > 2 && atoi(argv[i]) == 0) {
			printf("Divide by zero\n");
			exit(1);
		  }
		  divide = divide / atoi(argv[i]);
		}
		printf("%i\n", divide);
	  }
	}
  }
  return 0;
}

bool isvalid(char * s) {
  if (strcmp(s, "add") == 0 || strcmp(s, "mult") == 0 || strcmp(s, "div") == 0 || strcmp(s, "len") == 0)
	return true;
  else
	return false;
}

bool isinteger(char * s) {
  for (int i = 0; i < strlen(s); i++) {
	if (!my_isdigit(s[i]))
		return false;
  }
	return true;
}

bool my_isdigit(char c) {
  if (c >= '0' && c <= '9')
	return true;
  else
	return false;
}
