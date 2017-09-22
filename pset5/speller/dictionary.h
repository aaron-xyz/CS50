/**
 * Declares a dictionary's functionality.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// TRIE
typedef struct node
{
    bool is_word;
    struct node *children[27];
} node;

/**
  * Returns true if word is in dictionary else false.
  */
bool check(const char *word);

/**
  * Loads dictionary into memory. Returns true if successful else false.
  */
bool load(const char *dictionary);

/**
  * Returns number of words in dictionary if loaded else 0 if not yet loaded.
  */
unsigned int size(void);

/**
  * Unloads dictionary from memory.  Returns true if successful else false.
  */
bool unload(void);

/**
  * Free node -  fucntion support for unload
  */
void freeNode(node *ptr);

#endif // DICTIONARY_H
