/** Author: Aaron AP
 *
 * Description:
 * This program implements a linked queue and its main operations
 * [x] init
 * [x] empty
 * [x] enqueue
 * [x] dequeue
 * [x] print
 *
 */

#include <stdio.h>
#include <stdlib.h>

// constants
#define SIZE 10

// Struct of the linked queue
typedef struct node
{
    int val;
    struct node *next;
} node;

// Prototype
node *initList();
int isEmpty(node *list);
node *enqueue(node *list, int n);
node *dequeue(node *list);
void printQueue(node *list);

int main(void)
{
    // Init list
    node *first = initList();

    // insert values into the queue
    printf("Inserting %i random ints to the queue...\n", SIZE);

    int r = 0;

    // enqueue elements
    for (int i = 0; i < SIZE; i++)
    {
        r = rand() % 200;
        first = enqueue(first, r);
        printQueue(first);
    }

    printf("Your queue contains: ");
    printQueue(first);

    // dequeue elements
    for (int i = 0; i < SIZE/2; i++)
    {
        first = dequeue(first);
        printQueue(first);
    }

    printf("Your queue contains: ");
    printQueue(first);

    while (first != NULL)
    {
        first = dequeue(first);
    }

    first = dequeue(first);
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

// PREPEND
node *prepend(node *list, int n)
{
    // Allocate space
    node *temp = (node *)malloc(sizeof(node));

    // check allocation correctness
    if (temp == NULL)
    {
        fprintf(stderr, "Allocation error when inserting node.\n");
        exit(1);
    }
    // prepend node
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

// APPEND
node *enqueue(node *list, int n)
{
    // Allocate space for the new node
    node *temp = (node *)malloc(sizeof(node));

    // Check for allocation correctness
    if (temp == NULL)
    {
        printf("Memory allocation not possible\n");
        exit(1);
    }

    // Assign values for the new node
    temp->val = n;
    temp->next = NULL;

    // If the list is empty
    if (list == NULL)
    {
        // first points to new node
        list = temp;
        // make changes out of current scope
        return list;
    }
    else
    {
        // Copy the pointer of list
        node *ptr = list;

        // Check every node until find the last one
        while (ptr->next != NULL)
            ptr = ptr->next;

        // Link the previous last node with the new node
        ptr->next = temp;
    }

    return list;
}

// INSERT_SORTED
node *insertSorted(node *list, int n)
{
    // Otherwise allocate memory for the new node
    node *temp = (node *)malloc(sizeof(node));

    // Check for allocation correctness
    if (temp == NULL)
    {
        printf("Memory allocation not possible\n");
        exit(1);
    }

    // set values
    temp->val = n;
    temp->next = NULL;

    // ptr and list point the same
    node *prev = NULL;
    for (node *current = list; current != NULL; current = current->next)
    {
        // break if we find a value larger than i
        if (current->val > n)
        {
            break;
        }
        else
        {
            prev = current;
        }
    }

    // if new belongs at head, prepend
    if (prev == NULL)
    {
        temp->next = list;
        list = temp;
    }

    // else insert in middle or end
    else
    {
        temp->next = prev->next;
        prev->next = temp;
    }

    return list;
}

// ERASE
node *dequeue(node *list)
{
    // It will sotre the data in the node to be deleted
    int deleted = 0;

    // A pointer to the first element
    node *ptr = list;

    // Check if the list is empty
    if (ptr == NULL)
    {
        printf("Current list is already empty\n");
        exit(1);
    }
    else
    {
        // Head points to the next element
        list = ptr->next;
        // Save the data before be freed
        deleted = ptr->val;
        // Free the node
        free(ptr);
        // Delete the address too
        ptr = NULL;

        printf("Deleted: %i\n", deleted);
    }
    return list;
}

// SEARCH
int search(node *list, int n)
{
    // do not change first pointer
    node *ptr = list;

    // search until the end of the list
    while (ptr != NULL)
    {
        if (ptr->val == n)
        {
            return 1;
        }
        ptr = ptr->next;
    }
    // value not found
    return 0;
}

// LENGTH
int length(node *list)
{
    // initial length
    int initial_length = 0;

    // do not change first pointer
    node *ptr = list;

    // counting nodes
    while (ptr != NULL)
    {
        initial_length++;
        ptr = ptr->next;
    }

    return initial_length;
}

// PRINT
void printQueue(node *list)
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
