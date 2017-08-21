/** !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 1 - (http://docs.cs50.net/2016/fall/psets/1/pset1.html)
 * CREDIT: credit.c  - (http://docs.cs50.net/problems/credit/credit.html)
 * 
 * RECOGNIZING CREDIT CARDS:
 * This code identifies the type of credit card based on
 * its number. 
 * INPUT: a credit card number
 * OUTPUT: the name of the credit card: VISA , AMEX or MASTERCARD
 * 
 * VISA:
 * digits: 13 and 16
 * first digits: 4
 *
 * AMEX:
 * number of digits: 15
 * first digits: 34 or 37
 *
 * MASTERCARD:
 * number of digits: 16
 * first digits: 51, 52, 53, 54, or 55 
 *
 * Usage and example:
 * $ ./credit
 * Number: 378282246310005
 * AMEX
 * 
 */

#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void)
{
	// initial variables
    int counter, even, odd, sum, digit, double_digit;
    int digits[20];
    long long number_card;
    
    // Asking for the number
    printf("Number: ");
    number_card = get_long_long();
    
    counter = 0;
    even = 0;
    odd = 0;

    // Checking the number of digits. checking the Luhn's algorithm
    while(number_card)
    {
        // Getting modulus of 10 and storing them in digits
        digit = number_card % 10;
        
        // This array will store the digits of the credit card in separated digits
        // the order of te digits is swapped respect to its original order
        digits[counter] = digit;
        
        // Once the digit is stored can be truncated from the credit card number
        number_card /= 10;
        
        /* Acording to the Luhn's theorem
         * the 0-, 2-, 4- indexed and so on are added
         * the 1-, 3-, 5-, indexed and so on are multiplied by two and then added
         */
        if (counter % 2 == 0)
        {
            even = even + digit;
        }
        else
        {
            // If the number obtained after the multiplication is of two digits then are separated in
            // individual digits and then added.
            if (digit*2 > 9)
            {
                double_digit = digit*2;
                while (double_digit)
                {
                    odd = odd + ((double_digit) % 10);
                    double_digit /= 10;
                }
            }
            else
            {
                odd = odd + digit*2;
            }
        }
        counter++;
    }
    
    // The last digit of the sum must zero to be valid.
    sum = even + odd;
    
    // checking for Master Card and Visa for 16 digits
    if (counter == 16 && (sum % 10 == 0))
    {
        if ( digits[15] == 5 && ((digits[14] == 1) || (digits[14] == 2) || (digits[14] == 3) || (digits[14] == 4) || (digits[14] == 5)) )
        {
            printf("MASTERCARD\n");
        }
        else if (digits[15] == 4)
        {
            printf("VISA\n");
        }
    }
    
    // Checking for American Express
    else if (counter == 15 && (sum % 10 == 0))
    {
        if ( digits[14] == 3 && ((digits[13] == 7) || (digits[13] == 4)) )
        {
            printf("AMEX\n");
        }
    }
    
    // Checking for Visa with 13 digits
    else if ( counter == 13 && (sum % 10 == 0) )
    {
        if (digits[12] == 4)
        {
            printf("VISA\n");
        }
    }
    
    else
    {
        printf("INVALID\n");
    }
    
    // executed succesfully
    return 0;
}