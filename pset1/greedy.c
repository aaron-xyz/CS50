/* !! USING THE CS50 HEADER
 *
 * GREEDY ALGORITHM
 * in this algorithm
 * the user enter certain amount
 * of dollars and the program will return
 * the least necessary amount of coins
 * 
 * Example:
 * input: 5
 * least quantuty of coins: 20
 *
 * the coins to use are:
 * quarters: 0.25
 * dimes: 0.10
 * nickels: 0.05
 * pennies: 0.01
 *
 */

#include <stdio.h>
#include <math.h>
#include <cs50.h>

int main(void)
{
	// variables
    int owed_int, coins;
    float owed;
    
    coins = 0;
    
    // Just values above 0
    do
    {
        printf("O hai! How much change is owed?\n");
        owed = get_float();
    }
    while (owed < 0);
    
    // transforming float into int to avoid errors
    owed_int = (int)(roundf(owed*100));
    
    while(owed_int > 0)
    {
        if (owed_int >= 25)
        {
            owed_int -= 25;
            coins++;
        }
        else if (owed_int >= 10)
        {
            owed_int -= 10;
            coins++;
        }
        else if (owed_int >= 5)
        {
            owed_int -= 5;
            coins++;
        }
        else
        {
            owed_int -= 1;
            coins++;
        }
    }
    
    //Printing the minimum amount of coins
    printf("%i\n",coins);
}