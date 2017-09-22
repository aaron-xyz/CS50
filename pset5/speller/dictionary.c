/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include "dictionary.h"

// globals
node *root;
unsigned int dict_size = 0;
bool dict_loaded = false;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // local variables
    char s[LENGTH + 1];
    int index = 0, position = 0;
    node *ptr = root;

    // copy word in lowercase
    while (word[index] != '\0')
    {
        s[index] = tolower(word[index]);
        index++;
    }
    s[index] = word[index];

    // check if word is in dictionary or not
    for (int i = 0; i <= index; i++)
    {
        // whole word has been checked
        if (s[i] == '\0')
        {
            return ptr->is_word;
        }
        else
        {
            position = s[i] - 'a';
            // apostrophe position
            if (position < 0)
            {
                position = 26;
            }

            // word doesn't exist
            if (ptr->children[position] == NULL)
            {
                return false;
            }
            // the next letter
            else
            {
                ptr = ptr->children[position];
            }
        }
    }
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    // allocate memory for the root trie
    root = malloc(sizeof(node));
    if (root == NULL)
    {
        return false;
    }
    // init values for root
    root->is_word = false;
    for (int i = 0; i < 27; i++)
    {
        root->children[i] = NULL;
    }

    // get dictionary
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        unload();
        return false;
    }

    // traversing pointer
    int position = 0;
    node *ptr = root;

    // load word-by-word char-by-char
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    {
        if (c != '\n')
        {
            // which word position
            position = c - 'a';
            // apostrophe position
            if (position < 0)
            {
                position = 26;
            }

            // create new node
            if (ptr->children[position] == NULL)
            {
                // allocate memory space
                node *new_node = malloc(sizeof(node));
                if (new_node == NULL)
                {
                    return false;
                }
                // init new node
                new_node->is_word = false;
                for (int i = 0; i < 27; i++)
                {
                    new_node->children[i] = NULL;
                }

                // link the new node to the trie
                ptr->children[position] = new_node;
                ptr = ptr->children[position];
            }
            else
            {
                ptr = ptr->children[position];
            }
        }
        // make word valid and update counter
        else
        {
            ptr->is_word = true;
            dict_size++;
            ptr = root;
        }
    }
    fclose(dict);
    dict_loaded = true;
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    if (!dict_loaded)
    {
        return 0;
    }
    return dict_size;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    freeNode(root);
    if (root == NULL)
    {
        return true;
    }
    return false;
}
// auxiliar function with argument for recursivity
void freeNode(node *ptr)
{
    // unload node-by-node
    for (int i = 0; i < 27; i++)
    {
        // unload children nodes first if necessary
        if (ptr->children[i] != NULL)
        {
            freeNode(ptr->children[i]);
        }
    }
    // free root and make it NULL if possible
    if (ptr == root)
    {
        free(root);
        root = NULL;
        ptr = NULL;
        return;
    }
    // free current node
    free(ptr);
    ptr = NULL;
    return;
}
