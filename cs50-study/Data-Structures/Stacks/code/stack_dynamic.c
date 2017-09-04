/** Author: Aaron AP
 *
 * Description:
 * This program implements a linked list and its main operations
 * [x] init
 * [x] empty
 * [x] push
 * [x] pop
 *
 */

#include <stdio.h>
#include <stdlib.h>

// constants
#define SIZE 10

// Struct of the linked stack
typedef struct node
{
    int val;
    struct node *next;
} node;

// Prototype
node *initList();
int isEmpty(node *list);
node *push(node *list, int n);
node *pop(node *list);
void printStack(node *list);

int main(void)
{
    // Init list
    node *first = initList();

    // INSERT SORTED - NEED CORRECTIONS
    printf("Push %i random ints to the stack...\n", SIZE);

    int r = 0;

    // push elements
    for (int i = 0; i < SIZE; i++)
    {
        r = rand() % 200;
        first = push(first, r);
        printStack(first);
    }

    printf("Current stack: ");
    printStack(first);

    // pop elements
    for (int i = 0; i < SIZE/3; i++)
    {
        first = pop(first);
        printStack(first);
    }

    printf("Current stack: ");
    printStack(first);

    while (first != NULL)
    {
        first = pop(first);
    }
    first = pop(first);
}

/**
  * FUNCTIONS IMPLEMENTATION
  */

// INIT
node *initList()
{
    // memory allocation
    node *new = (node *)malloc(sizeof(node));

    // init and return pointer
    new = NULL;
    return new;
}

// IS EMPTY
int isEmpty(node *list)
{
    if (list == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// PUSH
node *push(node *list, int n)
{
    // Allocate space
    node *temp = (node *)malloc(sizeof(node));

    // check allocation correctness
    if (temp == NULL)
    {
        fprintf(stderr, "Allocation error when inserting node.\n");
        exit(1);
    }
    // push node
    else
    {
        // setting new node values
        temp->val = n;
        temp->next = list;
        // first points to new node
        list = temp;
        // make changes out of current scope
        return list;
    }
}

// POP
node *pop(node *list)
{
    // It will sotre the data in the node to be deleted
    int popped = 0;

    // A pointer to the first element
    node *ptr = list;

    // Check if the list is empty
    if (ptr == NULL)
    {
        printf("Current stack is already empty\n");
        exit(1);
    }
    else
    {
        // Head points to the next element
        list = ptr->next;
        // Save the data before be freed
        popped = ptr->val;
        // Free the node
        free(ptr);
        // Delete the address too
        ptr = NULL;

        printf("Popped: %i\n", popped);
    }
    return list;
}

// PRINT
void printStack(node *list)
{
    // setting bool for first element
    int first_element = 0;

    // pointer support
    node *ptr = list;

    // printing list
    while (ptr != NULL)
    {
        if (first_element == 0 && ptr->next == NULL)
        {
            printf("[%i]\n", ptr->val);
            first_element++;
            ptr = ptr->next;
        }
        else if (first_element == 0 && ptr->next != NULL)
        {
            printf("[%i, ", ptr->val);
            first_element++;
            ptr = ptr->next;
        }
        else if (ptr->next == NULL)
        {
            printf("%i]\n", ptr->val);
            ptr = ptr->next;
        }
        else
        {
            printf("%i, ", ptr->val);
            ptr = ptr->next;
        }
    }

    return;
}
