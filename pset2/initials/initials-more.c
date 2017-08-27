/** !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 2 - (http://docs.cs50.net/2017/x/psets/2/pset2.html)
 * INITIALS: initials-more.c  - (http://docs.cs50.net/problems/initials/more/initials.html)
 * 
 * INITIALS (MORE):
 * this program receives the name of a person and then prints out
 * it's intials in uppercase
 * INPUT: a name
 * OUTPUT: Initials
 *
 *
 * Usage and examples:
 * $ ./initials-more
 * Aaron Stone
 * AS
 *
 * $ ./initials-more
 * taylor swift
 * TS
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void)
{
    // INPUT
    string name = get_string();
    int index = 0;

    // string correctness
    if (name != NULL)
    {
        // until finish the string
        while (name[index] != '\0')
        {
            // Checking first character is letter
            if (index == 0 && name[index] != ' ')
            {
                printf("%c", toupper(name[index]));
            }
            // Just print initials
            else if (name[index] != ' ' && name[index-1] == ' ')
            {
                printf("%c", toupper(name[index]));
            }
            index++;
        }
        printf("\n");

        // succesful
        return 0;
    }

    // something went wrong
    return 1;
}
