/* !! USING THE CS50 HEADER
 *
 * This algorithm  ask the user
 * for the quantity of minutes
 * he spent in the shower and
 * return the equivalent quantity
 * in bottles of water
 *
 * 1 minute = 12 bottles of water
 * 3 minutes = 36 bottles of water
 *
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
	// variables
    int minutes;
    
    printf("Minutes: ");
    minutes = get_int();
    
    // The no training wheels way
    //scanf("%i", &minutes);
    
    printf("Bottles: %i\n", minutes*12);
    
    return 0;
}