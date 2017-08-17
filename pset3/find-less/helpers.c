/** !! USING THE CS50 HEADER
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Preventing odd results
    if (n < 1)
    {
        return false;
    }

    // binary search
    int size = n;
    int hi = n;
    int low = 0;
    int mid = (hi + low)/2;

    while (size > 0)
    {
        if (values[mid] == value)
        {
            return true;
        }
        else if (values[mid] < value)
        {
            low = mid + 1;
            mid = (hi + low)/2;
            size = size/2;
        }
        else
        {
            hi = mid - 1;
            mid = (hi + low)/2;
            size = size/2;
        }
    }


    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    bool swapped = false;
    int temp;

    // Bubble sort - O(n^2)
    for (int i = 0; i < n-1; i++)
    {
        // Reagrouping in ascending order pero pairs
        if (values[i] > values[i+1])
        {
            temp = values[i];
            values[i] = values[i+1];
            values[i+1] = temp;
            swapped = true;
        }

        // Check if the when we reach the last element there were some swaps
        // If yes check the array again
        if (i == n-2 && swapped)
        {
            i = -1;
            swapped = false;
        }
    }
    return;
}
