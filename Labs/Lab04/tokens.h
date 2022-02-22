#ifndef _tokens_h_
#define _tokens_h_

#include <stdio.h>
#include <stdbool.h>   // bool type
#include <stdlib.h>    // exit()
#include <string.h>

enum NUM_STATE {NON_DIGIT, DIGIT};  // states for a number
enum WORD_STATE {NON_WORD, WORD};   // states for a word

extern int const MAX_LENGTH;   // max length of a int

bool my_isdigit(char);       // returns true if char is a digit, false otherwise
bool my_isalpha(char);       // returns true if char is a letter, false otherwise
void parse_int(char *);      // parse int out of a string
void parse_word(char *);     // parse char out of a string

int  grow_number(char *, char, int);   // increase the int by a digit
void end_number(char *, int);          // end of an int

#endif
