/* !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 1 - (http://docs.cs50.net/2016/fall/psets/1/pset1.html)
 * GREEDY: greedy.c  - (http://docs.cs50.net/problems/greedy/greedy.html)
 *
 * GREEDY:
 * This code receives a certain quantity in dollars and returns
 * the least necessary amount of coins
 * INPUT: quantity of dollars
 * OUTPUT: least number of coins
 *
 * the coins to use are:
 * quarters: 0.25
 * dimes: 0.10
 * nickels: 0.05
 * pennies: 0.01
 *
 * Usage and examples:
 * $ ./greedy
 * O hai! How much change is owed?
 * 0.41
 * 4
 *
 * $ ./greedy
 * O hai! How much change is owed?
 * 5
 * 20
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
 
     // substract money until dollars become zero
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