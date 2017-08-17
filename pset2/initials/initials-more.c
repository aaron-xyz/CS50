/* !! USING THE CS50 HEADER
 *
 * INITIALS
 * this program receives the name of a person
 * theN prints it's intials in uppercase
 *
 * $ ./initials
 * Aaron Stone
 * AS
 *
 * $ ./initials
 * taylor swift
 * TS
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(void)
{
    // Ask for the name
    string name = get_string();
    int index = 0;

    // checking that the string is different to NULL
    if (name != NULL)
    {
        // Keep going until the end of the string
        while (name[index] != '\0')
        {
            // Checking if first character is different to space
            if (index == 0 && name[index] != ' ')
            {
                printf("%c", toupper(name[index]));
            }
            // Just print the character if the begining of a new word
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
