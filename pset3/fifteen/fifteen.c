/** !! USING THE CS50 HEADER
 *
 * CS50 2017 version
 * Problem Set 3 - (http://docs.cs50.net/2017/x/psets/3/pset3.html)
 * FIFTEEN: fifteen.c  - (http://docs.cs50.net/problems/fifteen/fifteen.html)
 *
 * FIFTEEN:
 * This algorithm implement the Game of Fifteen
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 * INPUT: BOARD-SIZE, tile-to-move
 * OUTPUT: BOARD-STATUS
 *
 * Usage and examples:
 * $ ./fifteen d
 *
 * $ ./fifteen 3
 * WELCOME TO GAME OF FIFTEEN
 *
 * 8  7  6
 *
 * 5  4  3
 *
 * 2  1  _
 *
 * Tile to move:
 *
 * Note:
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

 #define _XOPEN_SOURCE 500
 
 #include <cs50.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 
 // constants
 #define DIM_MIN 3
 #define DIM_MAX 9
 
 // board
 int board[DIM_MAX][DIM_MAX];
 
 // dimensions
 int d;
 
 // prototypes
 void clear(void);
 void greet(void);
 void init(void);
 void draw(void);
 bool move(int tile);
 bool won(void);
 
 int main(int argc, string argv[])
 {
     // ensure proper usage
     if (argc != 2)
     {
         printf("Usage: fifteen d\n");
         return 1;
     }
 
     // ensure valid dimensions
     d = atoi(argv[1]);
     if (d < DIM_MIN || d > DIM_MAX)
     {
         printf("Board must be between %i x %i and %i x %i, inclusive.\n",
             DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
         return 2;
     }
 
     // open log
     FILE *file = fopen("log.txt", "w");
     if (file == NULL)
     {
         return 3;
     }
 
     // greet user with instructions
     greet();
 
     // initialize the board
     init();
 
     // accept moves until game is won
     while (true)
     {
         // clear the screen
         clear();
 
         // draw the current state of the board
         draw();
 
         // log the current state of the board (for testing)
         for (int i = 0; i < d; i++)
         {
             for (int j = 0; j < d; j++)
             {
                 fprintf(file, "%i", board[i][j]);
                 if (j < d - 1)
                 {
                     fprintf(file, "|");
                 }
             }
             fprintf(file, "\n");
         }
         fflush(file);
 
         // check for win
         if (won())
         {
             printf("ftw!\n");
             break;
         }
 
         // prompt for move
         printf("Tile to move: ");
         int tile = get_int();
 
         // quit if user inputs 0 (for testing)
         if (tile == 0)
         {
             break;
         }
 
         // log move (for testing)
         fprintf(file, "%i\n", tile);
         fflush(file);
 
         // move if possible, else report illegality
         if (!move(tile))
         {
             printf("\nIllegal move.\n");
             usleep(500000);
         }
 
         // sleep thread for animation's sake
         usleep(500000);
     }
 
     // close log
     fclose(file);
 
     // success
     return 0;
 }
 
 /**
  * Clears screen using ANSI escape sequences.
  */
 void clear(void)
 {
     printf("\033[2J");
     printf("\033[%d;%dH", 0, 0);
 }
 
 /**
  * Greets player.
  */
 void greet(void)
 {
     clear();
     printf("WELCOME TO GAME OF FIFTEEN\n");
     usleep(2000000);
 }
 
 /**
  * Initializes the game's board with tiles numbered 1 through d*d - 1
  * (i.e., fills 2D array with values but does not actually print them).
  */
 void init(void)
 {
     // TODO
     // defining dimensions
     int tile = d*d - 1;
 
     // hold the values to swap
     int holder, holder2;
 
     for (int i = 0; i < d; i++)
     {
         for (int j = 0; j < d; j++)
         {
             // Show the empty space with an underscore
             if (tile == 0)
             {
                 //tile = '_';
                 board[i][j] = tile;
             }
             // while tile greater than zero fill the array with numbers
             else
             {
                 board[i][j] = tile;
             }
             tile--;
         }
     }
 
     // Swap 1 and 2 when d is even. Keep the same if odd.
     if (d%2 == 0)
     {
         holder = board[d-1][d-3];
         holder2 = board[d-1][d-2];
         board[d-1][d-3] = holder2;
         board[d-1][d-2] = holder;
     }
 
 }
 
 /**
  * Prints the board in its current state.
  */
 void draw(void)
 {
     // TODO
     for (int i = 0; i < d; i++)
     {
         for (int j = 0; j < d; j++)
         {
             // show ascii code
             //if (board[i][j] == '_')
             if (board[i][j] == 0)
             {
                 // What distance should the undescore take
                 //printf("  %c ",board[i][j] );
                 printf("  %i ",board[i][j] );
             }
             else
             {
                 // Add an extra space if the number is of one digit only.
                 // This gives simmetry to the board
                 if (board[i][j] < 10)
                 {
                     printf("  %i ", board[i][j]);
                 }
                 else
                 {
                     printf(" %i ", board[i][j]);
                 }
             }
         }
         printf("\n");
     }
 
 }
 
 /**
  * If tile borders empty space, moves tile and returns true, else
  * returns false.
  */
 bool move(int tile)
 {
     // TODO
     //int empty = 95; // Comnent for test in CS50
     int empty = 0;
     int row, column;
     bool found = false;
 
     if (tile > d*d - 1 || tile < 1)
     {
         return false;
     }
 
     for (int i = 0; i < d; i++)
     {
         for (int j = 0; j < d; j++)
         {
             // store the coordinates of the typed tile
             if (board[i][j] == tile)
             {
                 row = i;
                 column = j;
                 found = true;
                 break;
             }
         }
         if (found)
         {
             break;
         }
     }
 
     // checking the upper and the lower rows
     // Is it the upper tile empty?
     if ( (board[row - 1][column] == empty) && row > 0)
     {
         board[row - 1][column] = tile;
         board[row][column] = empty;
         return true;
     }
     // Is ti the lower tile empty?
     else if ( (board[row + 1][column] == empty) && row < d-1)
     {
         board[row + 1][column] = tile;
         board[row][column] = empty;
         return true;
     }
 
     // checking the left and the right columns
     // Is it the left tile empty?
     else if ( (board[row][column - 1] == empty) && column > 0)
     {
         board[row][column - 1] = tile;
         board[row][column] = empty;
         return true;
     }
     // Is it the right tile empty?
     else if ( (board[row][column + 1] == empty) && column < d-1)
     {
         board[row][column + 1] = tile;
         board[row][column] = empty;
         return true;
     }
 
 
     return false;
 }
 
 /**
  * Returns true if game is won (i.e., board is in winning configuration),
  * else false.
  */
 bool won(void)
 {
     // TODO
     int count = 0;
     int square = d*d;
 
     for (int i = 0; i < d; i++)
     {
         for (int j = 0; j < d; j++)
         {
             //  count always must be equal to the current tile.
             // if not then the board have not the tiles in winner position
             count++;
             if (board[i][j] != count && count < square)
             {
                 return false;
             }
         }
     }
 
     return true;
 }