/* !! USING THE CS50 HEADER
 *
 * This algorithm prints a half-left-pyramid
 * similar to those from the Mario Bros Game
 * 
 * from height 0 to 23
 * with rectangles of (base)*(height) = (height + 1)(height)
 *
 * The following pyramid is an example
 * of a half pyramid with height 3
 *
 *   ##
 *  ###
 * ####
 * 
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
	// variables
    int height, spaces;
    
    // repeat until get a number between 0 and 23 inclusive
    do
    {
        printf("Height: ");
        height = get_int();
    } 
    while(height > 23 || height < 0);
    
    // Creating a flag to do not change the original variable
    spaces = height;
    
    // loops to create the pyramid
    // create the columns (columnas)
    for (int columnas = 0; columnas < height; columnas++)
    {
        spaces--;
        // create the rows (filas)
        for (int filas = 0; filas < height+1; filas++)
        {
            if (filas <= spaces - 1)
            {
                printf(" ");
            }
            else 
            {
                printf("#");
            }
        }
        printf("\n");
    }
    
    return 0;
}