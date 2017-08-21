/** CS50 2017 version
 * Problem Set 1 - (http://docs.cs50.net/2016/fall/psets/1/pset1.html)
 * WATER: water.c  - (http://docs.cs50.net/problems/water/water.html)
 *
 * HELLO, WORLD!:
 * This code ask the user for the quantity of minutes he spent in the shower and
 * return the equivalent quantity in bottles of water
 * INPUT: Number of minutes
 * OUTPUT: Number of bottles of water
 *
 * 1 minute = 12 bottles of water
 *
 * Usage and examples:
 * $ ./water
 * Minutes: 1
 * Bottles: 12
 *
 * $ ./water
 * Minutes: 10
 * Bottles: 120
 *
 */

 #include <stdio.h>
 #include <cs50.h>

 int main(void)
 {
     // initial variables
     int minutes;

     // asking for input
     do {
         printf("Minutes: ");
         minutes = get_int();
     } while (minutes < 0);

     // Output
     printf("Bottles: %i\n", minutes*12);

     return 0;
 }