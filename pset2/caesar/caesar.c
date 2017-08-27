/** !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 2 - (http://docs.cs50.net/2017/x/psets/2/pset2.html)
 * CAESAR: caesar.c  - (http://docs.cs50.net/problems/caesar/caesar.html)
 *
 * 
 * CAESAR:
 * This algorithm cipher text using the caesar cipher.
 * You must ENTER the KEY (a positive integer) on command line intarface (CLI)
 * otherwise a warning is printed.
 * INPUT: KEY, plaintext
 * OUTPUT: ciphertext
 *
 *
 * Usage and examples:
 * $ ./caesar 13
 * plaintext:  HELLO
 * ciphertext: URYYB
 *
 * $ ./caesar 2
 * plaintext: abc
 * ciphertext: cdf
 *
 * $ ./caesar 2
 * plaintext: xYz
 * ciphertext: zAb
 *
 * $ ./caesar
 * You must enter the key: ./caesar KEY
 *
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
        printf("You must enter the key: ./caesar KEY\n");
        return 1;
    }

    // from string to int
    int key = atoi(argv[1]);

    // input
    printf("plaintext: ");
    string p = get_string();

    string c = p;

    // looping through every char in the plaintext - Just change alphabetic chars
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
    
    // output
    printf("ciphertext: %s\n",c);

    // success
	return 0;
}
