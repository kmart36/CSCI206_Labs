/*
 * Implements a dictionary's functionality
 * Katy Martinson
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Maximum number of words in the dictionary
#define N 150000

// Hash bins
#define BINS 27

// array of dictionary words
char words[BINS][N][LENGTH+1];

// number of words in the dictionary
int num_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
  unsigned int bin = hash(word);
  for (int i = 0; i < N; i++) {
	if (strcasecmp(word, words[bin][i]) == 0) {
	  return true;
	}
  }
  return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary_filename)
{
  FILE * fp = fopen(dictionary_filename, "r");
  if (fp == NULL)
	return false;
  char word[LENGTH + 1];
  num_words = 0;
  unsigned int bin;
  while(fgets(word, LENGTH + 1, fp) != NULL && num_words < N) {
	// Will calculate the bin that the word should go in each time a new word is found. 
	if (strlen(word) > 1) {
	  word[strlen(word) - 1] = '\0';
	  bin = hash(word);
	  strcpy(words[bin][num_words], word);
	  num_words++;
	}
  }
  return true;
}

// Return the number of words stored in the dictionary.
unsigned int size(void)
{ 
  return num_words;
}

// Will return the integer value of the first character of the given word, starting with 'a' being 0
// and 'z' being 25. If the word starts with a non-letter, it will be added to the bin at index 26.
unsigned int hash(const char *word) {
  if (isalpha(word[0]) == 0)
	return 26;
  char c = tolower(word[0]);
  return (unsigned int) c - 97;
}
