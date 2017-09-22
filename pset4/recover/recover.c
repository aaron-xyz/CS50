/** Aaron AP
 *
 * CS50 2017 version
 * Problem Set 4 - (http://docs.cs50.net/2017/x/psets/4/pset4.html)
 * RECOVER: resize.c  - (http://docs.cs50.net/problems/recover/recover.html)
 *
 * RECOVER:
 * This program recover images
 * from a memory card (raw file)
 *
 * Usage:
 * compile: make recover
 * execute: $ ./recover card.raw
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// unsigned int of 8 bits (1 Byte)
typedef uint8_t BYTE;
// size of the block
#define BLOCKSIZE 512

int main(int argc, char *argv[])
{
    // Check correct input
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }

    // open card file
    FILE *raw_file = fopen(argv[1], "r");

    // if raw_file is NULL (non-existent file)
    if (raw_file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // open output file
    FILE *outfile;
    outfile = NULL;

    // create a variable to name the new image files
    int img_num = 0;

    // forever loop that will end when the file has been read
    while (1)
    {
        // create an array called block that's the size of BLOCKSIZE
        BYTE block[BLOCKSIZE] = {};

        // iterate over each byte in each block until you reach the end of the file
        for (int i = 0; i < BLOCKSIZE; i++)
        {
            // if you reach the end of file, close the file
            if (feof(raw_file))
            {
                fclose(raw_file);

                // close previously opened output file pointer if necessary
                if (outfile != NULL)
                    fclose(outfile);

                return 0;
            }

            // read one byte at a time
            fread(&block[i], sizeof(BYTE), 1, raw_file);
        }

        // if block's first 4 bytes match those of a jpg (start of new jpg)
        if ((block[0] == 0xff) && (block[1] == 0xd8) && (block[2] == 0xff) && (block[3] == 0xe0 || block[3] == 0xe1))
        {
            // close previously opened output file pointer if necessary
            if (outfile != NULL)
            {
                fclose(outfile);
            }

            // create a constant char array for filename
            char filename[4];

            // name file using ###.jpg format
            sprintf(filename, "%03d.jpg", img_num);
            img_num++;

            // open the output file pointer and make sure it's not NULL
            if ((outfile = fopen(filename, "w")) == NULL)
            {
                printf("Could not write image.\n");
                return 1;
            }

            // write the block containing the photo to the outfile
            fwrite(&block[0], BLOCKSIZE * sizeof(BYTE), 1, outfile);
        }

        // if outfile has been opened, write the block to the outfile
        else if (outfile != NULL)
        {
            fwrite(&block[0], BLOCKSIZE * sizeof(BYTE), 1, outfile);
        }
    }

    // close file
    fclose(raw_file);

    // return 0 to exit program
    return 0;
}
