/* Katy Martinson
 * Tuesday 1pm
 * Section 61
 * File name: head.c
 * Compile with: make head
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


const int MAXLINES = 100;
const int MAXBYTE = 255;
int read_file_lines(FILE *, char [MAXLINES][MAXBYTE + 1], int);

int main(int argc, char * argv[]) {
  FILE* fp;
  fp = fopen(argv[1], "r");
  char buffer[MAXLINES][MAXBYTE + 1];
  if (argc < 3)
	read_file_lines(fp, buffer, 10);
  else
    read_file_lines(fp, buffer, atoi(argv[2]));
  return 0;
}

int read_file_lines(FILE * fp, char buffer[MAXLINES][MAXBYTE + 1],
					int lines_expected) {
  int line = 0;
  if (fp == NULL) {
	printf("fopen failed: No such file or directory\n");
	exit(0);
  }
  while (fgets(buffer[line], MAXBYTE, fp) != NULL && line < lines_expected) {
	printf("%s", buffer[line]);
	line++;
  }
  fclose(fp);
  return line;
}
