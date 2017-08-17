/* !! USING THE CS50 HEADER
 *
 * This algorithm cipher using the caesar cipher
 *
 *
 * As input you must enter a key after the name of the program
 * the key must be a positive integer
 * if you do not input the key or you write other things than the key
 * the program will return error
 *
 * the key is use to cipher your plaintext
 * you are asked to input your plaintext after checking you typed your key correctly
 *
 * Examples
 * $ ./caesar 2
 * abc
 * cdf
 *
 * $ ./caesar 2
 * xYz
 * zAb
 *
 * $ .caesar
 * You must enter a key: ./caesar key
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    // The arguments must be exactly 2
    if (argc != 2)
    {
        printf("You must enter the key:\n./caesar k\n");
        return 1;
    }

    // transforming from string to int
    int key = atoi(argv[1]);

    // asking for the plaint text and defininf variables
    printf("plaintext: ");
    string p = get_string();
    string c = p;

    /* TEST

    int lenp = strlen(p);
    char c[lenp + 1];

       TEST
    */

    // looping through the plaintext
    for (int i = 0, p_len = strlen(p); i < p_len; i++)
    {

        // is a letter?
        if (isalpha(p[i]))
        {
            // is uppercase?
            if isupper(p[i])
            {
                c[i] = ((p[i] - 'A' + key)%26) + 'A';
            }
            // or is it lowercase?
            else if islower(p[i])
            {
                c[i] = ((p[i] - 'a' + key)%26) + 'a';
            }
        }
    }

    printf("ciphertext: %s\n",c);

	return 0;
}
