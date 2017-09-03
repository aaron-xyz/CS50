/** Author: Aaron AP
 *
 * Description:
 * Write a program that prompts the user to input 
 * the names of five Pokemon. Store those Pokemon in an array,
 * and randomly select one to print out.
 *
 * Usage:
 * $ ./pokemon
 * Give me a Pokemon: Butterfree
 * Give me a Pokemon: Clefairy
 * Give me a Pokemon: Diglett
 * Give me a Pokemon: Growlithe
 * Give me a Pokemon: Rapidash
 * Clefairy, I choose you!
 * 
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX 5

int main(int argc, char *argv[])
{
    // declare array storage for Pokemon
    char *pokemon[MAX];
    char name[20];

    // collect and store Pokemon
    for (int i = 0; i < 5; i++)
    {
        printf("Give me a Pokemon: ");
        scanf("%s", name);
        pokemon[i] = name;
    }

    // initialize random seed
    srand(time(NULL));

    // choose and print out random Pokemon
    printf("pokemon[%i]: %s, I choose you!\n", rand() % 5, pokemon[rand() % 5]);
}
