/**
 * This program is a simple implementation of
 * a hash table.
 * This program implemente a hash function for strings 
 * that sums the ASCII values of the argument key's characters.
 *
 * $ ./hash
 * Hash table size: 100
 * Key: puppy
 * The string 'puppy' is mapped to index 74
 *
 * $ ./hash
 * Hash table size: 100
 * Key: PUPPY
 * The string 'puppy' is mapped to index 14.
 *
 */

#include <stdio.h>

#define HASH_SIZE 100

// prototype
int hash_function(char *key, int size);

int main(void)
{
    char str[100];
    
    printf("Hash table size: %i\n", HASH_SIZE);

    printf("key: ");
    scanf("%s", str);

    printf("The string %s is mapped to index %i\n", str, hash_function(str, HASH_SIZE));
}

// HASH FUNCTION IMPLEMENTATION
int hash_function(char *key, int size)
{
    int index = 0;

    for (int i = 0; key[i] != '\0'; i++)
    {
        index += key[i];
    }
    return index % size;
}