/** !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 3 - (http://docs.cs50.net/2017/x/psets/3/pset3.html)
 * FIND-LESS: find-less.c  - (http://docs.cs50.net/problems/find/less/find.html)
 *
 * FIND-LESS:
 * This algorithm Implement a program that finds a number (needle) among numbers.
 * where needle is the value to find in a haystack of values
 * INPUT: needle
 * OUTPUT: bool - found or not found
 *
 * Usage ad examples
 * $ ./find 42
 * 50
 * 43
 * ^d
 * Didn't find needle in haystack.
 *
 * $ ./find 42
 * 50
 * 42
 * ^d
 * Found needle in haystack!
 *
 * $ ./generate 1000 | ./find 42
 * Didn't find needle in haystack.
 *
 * $ ./generate 1000 50 | ./find 127
 * Found needle in haystack!
 *
 * $ ./generate 1000 50 | ./find 128
 * Didn't find needle in haystack.
 *
 */

 #include <cs50.h>
 #include <stdio.h>
 #include <stdlib.h>
 
 #include "helpers.h"
 
 // maximum amount of hay
 const int MAX = 65536;
 
 int main(int argc, string argv[])
 {
     // ensure proper usage
     if (argc != 2)
     {
         printf("Usage: ./find needle\n");
         return -1;
     }
 
     // remember needle
     int needle = atoi(argv[1]);
 
     // fill haystack
     int size;
     int haystack[MAX];
     for (size = 0; size < MAX; size++)
     {
         // wait for hay until EOF
         printf("\nhaystack[%i] = ", size);
         int straw = get_int();
         if (straw == INT_MAX)
         {
             break;
         }
 
         // add hay to stack
         haystack[size] = straw;
     }
     printf("\n");
 
     // sort the haystack
     sort(haystack, size);
 
     // try to find needle in haystack
     if (search(needle, haystack, size))
     {
         printf("\nFound needle in haystack!\n\n");
         return 0;
     }
     else
     {
         printf("\nDidn't find needle in haystack.\n\n");
         return 1;
     }
 }
 