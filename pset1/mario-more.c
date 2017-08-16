/* !! USING THE CS50 HEADER
 * 
 *
 * Mario second version
 * in this version it will be
 * printed 2 half pyramids instead 1
 * from height 0 to 23 iclusive
 * 
 * The following pyramid is an example
 * of two half pyramids with height 3
 *
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
    
    // check that the height is between 0 and 23 inclusive
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