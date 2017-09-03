/** Author: Aaron AP
 * 
 * Description:
 * This program prompts the user to input 5 integers.
 * Store the integers in an array, and print out the average of their values.
 *
 * $ ./average
 * Give me an integer: 4
 * Give me an integer: 1
 * Give me an integer: 5
 * Give me an integer: 10
 * Give me an integer: 5
 * Average: 5
 *
 */

#include <stdio.h>

#define N 5

int main(void)
{
    // Define array
    int number[5];
    int sum = 0;
    int average = 0;

    // Get the numbers
    for (int i = 0; i < N; i++)
    {
        printf("Give me an integer: ");
        scanf("%i", &number[i]);
        sum += number[i];
    }

    // Print the average
    average = sum/N;
    printf("Average: %i\n", average);

    return 0;
}
