/* !! USING THE CS50 HEADER
 *
 * Vigenere cipher
 *
 * ./vigenere key
 *
 * receives as input a key on command line (string)
 * receives a plaintext (string)
 * returns a ciphertext (string)
 *
 */

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // Just one key (string) after the name of the program  must be entered
    if (argc != 2)
    {
        printf("You must enter a key: ./vigenere key\n");
        return 1;
    }
    // Every char of k must be a letter
    string k = argv[1];
    int lk = strlen(argv[1]);

    // Testing every char of k
    for (int i = 0; i < lk; i++)
    {
        // return error if a char is different to a letters
        if ( !(isalpha(k[i])) )
        {
            printf("k is not alpha: ./vigenere k\n");
            return 1;
        }
    }

    // Ask for the plain text
    printf("plaintext: ");
    string p = get_string();

    // more variables
    string c = p;
    int lp = strlen(p);
    int j = 0;

    // Looping through the plaintext (p)
    for (int i = 0; i < lp; i++)
    {

        // the char of p is letter and uppercase
        if (isalpha(p[i]) && isupper(p[i]))
        {
            // When a char of k is uppercase
            if ( isupper(k[j]) )
            {
                c[i] = (( (p[i] - 'A') + (k[j] - 'A') )%26) + 'A';
            }
            else
            {
                c[i] = (( (p[i] - 'A') + (k[j] - 'a') )%26) + 'A';
            }

            // j must iterate just over index of k
            j = (j+1)%lk;
        }

        // the char of p is letter and lowercase
        else if ( isalpha(p[i]) && islower(p[i]) )
        {
            // When a char of k is lowercase
            if (islower(k[j]))
            {
                c[i] = (( (p[i] - 'a') + (k[j] - 'a') )%26) + 'a';
            }
            else
            {
                c[i] = (( (p[i] - 'a') + (k[j] - 'A') )%26) + 'a';
            }

            // j must iterate just over index of k
            j = (j+1)%lk;
        }
    }

    printf("ciphertext: %s\n", c);
	
    return 0;
}
