/* !! USING THE CS50 HEADER
 *
 *
 * CS50 2017 version
 * Problem Set 2 - (http://docs.cs50.net/2017/x/psets/2/pset2.html)
 * VIGENERE: vigenere.c  - (http://docs.cs50.net/problems/vigenere/vigenere.html)
 *
 * 
 * VIGENERE:
 * This algorithm cipher text using the vigenere cipher.
 * You must ENTER the KEY (a phrase) on command line intarface (CLI)
 * otherwise a warning is printed.
 * INPUT: KEY, plaintext
 * OUTPUT: ciphertext
 *
 *
 * Usage and examples:
 * $ ./vigenere ABC
 * plaintext:  HELLO
 * ciphertext: HFNLP
 *
 * $ ./vigenere
 * You must enter the key: ./vigenere KEY
 *
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // Check command line input correctness
    if (argc != 2)
    {
        printf("You must enter the key: ./vigenere KEY\n");
        return 1;
    }
    // Every char of k must be a letter
    string k = argv[1];
    int lk = strlen(argv[1]);

    // Testing every char of k
    for (int i = 0; i < lk; i++)
    {
        // return error if a char is not a letter
        if ( !(isalpha(k[i])) )
        {
            printf("k must be alpha: ./vigenere k\n");
            return 1;
        }
    }

    // INPUT
    printf("plaintext: ");
    string p = get_string();

    // variables
    string c = p;
    int lp = strlen(p);
    int j = 0;

    // Looping through the plaintext (p)
    for (int i = 0; i < lp; i++)
    {
        // is an uppercase letter?
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
            j = (j + 1) % lk;
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
            j = (j + 1) % lk;
        }
    }
    
    // OUTPUT
    printf("ciphertext: %s\n", c);
	
    // success
    return 0;
}
