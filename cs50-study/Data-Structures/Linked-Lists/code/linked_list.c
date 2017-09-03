/** Author: Aaron AP
 *
 * Description:
 * This program implements a linked list and its main operations
 * [x] init
 * [x] empty
 * [x] prepend
 * [x] append
 * [x] search
 * [x] delete front
 * [x] length
 * [x] print
 * [ ] delete all
 * [x] prepend sorted
 *
 */

#include <stdio.h>
#include <stdlib.h>

// constants
#define SIZE 10

// Struct of the linked list
typedef struct node
{
    int val;
    struct node *next;
} node;

// Prototype
node *initList();
int isEmpty(node *list);
node *prepend(node *list, int n);
node *append(node *list, int n);
node *insertSorted(node *list, int n);
node *deleteFirst(node *list);
int search(node *list, int n);
int length(node *list);
void printList(node *list);

int main(void)
{
    // Init list
    node *first = initList();

    /* LENGTH
      printf("Making sure the list length is indeed %i...\n", guessed_len);
      if (guessed_len == length(first))
      {
          printf("good!\n");
      }
      else
      {
          printf("wrong!\nThe correct length is %i\n", length(first));
      }
      */

    /* PREPEND
      printf("Prepending ints 0-9 onto the list...\n");
  
      // prepending elements
      for (int i = 0; i < 5; i++)
      {
          first = prepend(first, i);
          printList(first);
      }
      printf("Your list contains: ");
      printList(first);
  
      while (first != NULL)
      {
          first = deleteFirst(first);
      }
  
      first = deleteFirst(first);
      */

    /* SEARCH
      int value;
  
      // prepending elements
      for (int i = 0; i < 5; i++)
      {
          first = prepend(first, i);
      }
  
      // input
      printf("What value are you looking for? ");
      scanf("%i", &value);
  
      // found
      if (search(first, value) == 1)
      {
          printf("%i is in the list!\n", value);
      }
      // not found
      else
      {
          printf("Sorry, the list only contains: ");
          printList(first);
      }
      // delete list - free space
      while (first != NULL)
      {
          first = deleteFirst(first);
      }
  
      first = deleteFirst(first);
      */

    /* APPEND
      printf("Appending ints 0-9 onto the list...\n");
  
      // appending elements
      for (int i = 0; i < SIZE; i++)
      {
          first = append(first, i);
          printList(first);
      }
  
      printf("Your list contains: ");
      printList(first);
  
      while (first != NULL)
      {
          first = deleteFirst(first);
      }
  
      first = deleteFirst(first);
      */

    // INSERT SORTED - NEED CORRECTIONS
    printf("Inserting %i random ints to the list...\n", SIZE);

    int r = 0;

    // insert elements
    for (int i = 0; i < SIZE; i++)
    {
        r = rand() % 200;
        first = insertSorted(first, r);
        printList(first);
    }

    printf("Your list contains: ");
    printList(first);

    while (first != NULL)
    {
        first = deleteFirst(first);
    }

    first = deleteFirst(first);
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
node *append(node *list, int n)
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
node *deleteFirst(node *list)
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
void printList(node *list)
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
