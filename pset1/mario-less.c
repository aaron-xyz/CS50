/* !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 1 - (http://docs.cs50.net/2016/fall/psets/1/pset1.html)
 * MARIO-LESS: mario-less.c  - (http://docs.cs50.net/problems/mario/less/mario.html)
 *
 * MARIO (LESS):
 * This code prints a half-left-pyramid similar to those from 
 * the Mario Bros Game from height 0 to 23. 
 * INPUT: height of the pyramid
 * OUTPUT: a half-left pyramid
 *
 * Rectangles of dimensions: (base)*(height) = (height + 1)*(height)
 *
 * Usage and examples:
 * $ ./mario-less
 * Height: 5
 *     ##
 *    ###
 *   ####
 *  #####
 * ######
 * 
 * $ ./mario-less
 * Height: 3
 *   ##
 *  ###
 * ####
 * 
 */

#include <stdio.h>
#include <cs50.h>

int main(void)
{
	// initial variables
    int height, spaces;
    
    // repeat until get a number between 0 and 23 (inclusives)
    do
    {
        printf("Height: ");
        height = get_int();
    } 
    while(height > 23 || height < 0);
    
    // Creating a flag to do not change the original variable
    spaces = height;
    
    // loops to create the pyramid
    // create the columns
    for (int columnas = 0; columnas < height; columnas++)
    {
        spaces--;
        // create the rows
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