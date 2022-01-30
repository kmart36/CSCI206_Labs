/*
 * File name: cmd_args.c
 * Compile with: gcc -std=c99 cmd_args.c -o cmd_args
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isvalid(char * s);
bool isinteger(char * s);
bool my_isdigit(char c);

int main(int argc, char * argv[]) {
  if (argc < 2) {
	  printf("Incorrect number of arguments.\n");
	  exit(1);
  }
  else {
	if (isvalid(argv[1])) {
		printf("\"%s\" is a valid command\n", argv[1]);
	} 
	else {
		printf("\"%s\" is an invalid command\n", argv[1]);
	}	  
	for (int i = 2; i < argc; ++i) {
		if (isinteger(argv[i]))
		  printf("%s is an integer\n", argv[i]);
		else
		  printf("%s is not an integer\n", argv[i]);
	}
  }    
  return 0;	 
}

bool isvalid(char * s) {
  if (strcmp(s, "add") == 0 || strcmp(s, "sub") == 0 || strcmp(s, "mult") == 0 || strcmp(s, "div") == 0)
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
