/** Author: Aaron AP
 *
 * This program implement a binary search tree (BST) and
 * its basic functions.
 * [x] insert
 * [x] search
 * 
 */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define NODES 10;

// node bst structure
typedef struct node
{
    int n;
    struct node *left;
    struct node *right;
} node;

// global variables
node *root;

// prototype
bool insert(int val);
bool search(node *root, int val);

int main(void)
{
    // init tree
    root = NULL;

    // testing insert
    for (int i = 0; i < NODES; i++)
    {
        printf("Inserting %i ...%s!\n", i, insert(i) ? "success" : "fail");
    }
    for (int i = 0; i < NODES; i++)
    {
        printf("Tree contains %i? %s\n", i, search(root, i) ? "true" : "false");
    }

    return 0;
}

// INSERT
bool insert(int val)
{
    // the first node
    if (root == NULL)
    {
        node *first = malloc(sizeof(node));
        if (first == NULL)
        {
            fprintf(stderr, "Allocation error!\n");
            exit(1);
        }
        first->n = val;
        first->left = NULL;
        first->right = NULL;
        root = first;
        return true;
    }

    // search for insertion point
    node *current = root;
    node *prev = NULL;
    while (current != NULL)
    {
        prev = current;
        if (current->n < val)
        {
            current = current->right;
        }
        else if (current->n > val)
        {
            current = current->left;
        }
        else
        {
            return false;
        }
    }

    // build new node
    node *new = malloc(sizeof(node));
    if (new == NULL)
    {
        return false;
    }
    new->n = val;
    new->left = NULL;
    new->right = NULL;

    // insert node
    if (prev->n > val)
    {
        prev->left = new;
    }
    else
    {
        prev->right = new;
    }
    return true;
}

// SEARCH
bool search(node *root, int val)
{
    // if root is NULL
    if (root == NULL)
    {
        // return false
        return false;
    }
    // if root->n is val
    if (root->n == val)
    {
        // return true
        return true;
    }
    // if val is less than root->n
    else if (val < root->n)
    {
        // search left child
        return search(root->left, val);
    }
    // if val is greater than root->n
    else
    {
        // search right child
        return search(root->right, val);
    }
}