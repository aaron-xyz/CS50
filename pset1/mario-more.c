/* !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 1 - (http://docs.cs50.net/2016/fall/psets/1/pset1.html)
 * MARIO-LESS: mario-more.c  - (http://docs.cs50.net/problems/mario/more/mario.html)
 *
 * MARIO (LESS):
 * This code prints a two half-pyramids (left and right) similar to those from
 * the Mario Bros Game from height 0 to 23.
 * INPUT: height of the pyramid
 * OUTPUT: a half-left pyramid
 *
 * Rectangles of dimensions: (base)*(height) = (height)*(height)
 *
 * Usage and examples:
 * $ ./mario
 * Height: 4
 *    #  #
 *   ##  ##
 *  ###  ###
 * ####  ####
 *
 * $ ./mario-less
 * Height: 3
 *   #  #
 *  ##  ##
 * ###  ###
 *
 */

 #include <stdio.h>
 #include <cs50.h>
 
 int main(void)
 {
     // variables
     int height, spaces;
     int blocks = 0;
 
     // check height is between 0 and 23 inclusive
     do
     {
         printf("Height: ");
         height = get_int();
     }
     while(height < 0 || height > 23);
 
     spaces = height;
 
     // i -> rows
     // j -> columns
     for (int i = 0; i < height; i++)
     {
         // first (Left) pyramid
         for (int j = 0; j < height; j++)
         {
             if (j < spaces - 1)
             {
                 printf(" ");
             }
             else
             {
                 printf("#");
                 blocks++;
             }
         }
 
         // Separation between pyramids
         printf("  ");
 
         // Second (Right) pyramid
         for (int k = height; k > 0; k--)
         {
             if (blocks > 0)
             {
                 printf("#");
             }
             else
             {
                 break;
             }
             blocks--;
         }
 
         spaces--;
         printf("\n");
     }
 
     return 0;
 }