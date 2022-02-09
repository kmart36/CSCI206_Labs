/*
 * Implements a dictionary's functionality
 * Katy Martinson
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Maximum number of words in the dictionary
#define N 150000

// array of dictionary words
char words[N][LENGTH+1];

// number of words in the dictionary
int num_words = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
  for (int i = 0; i < N; i++) {
	if (strcasecmp(word, words[i]) == 0) {
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
  while(fgets(word, LENGTH + 1, fp) != NULL && num_words < N) {
	//if (word[strlen(word) - 1] == '\n' && strlen(word) > 1)
	if (strlen(word) > 1) {
	  word[strlen(word) - 1] = '\0';
	  strcpy(words[num_words], word);
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
