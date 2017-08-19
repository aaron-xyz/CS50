/**
 * This program
 * Resize a BMP from a scale from 1 to 100 (inclusive)
 *
 * Usage:
 * ./resize scale infile.bmp ourfile.bmp
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage (program name plus three elements)
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]); // scale
    char *infile = argv[2];
    char *outfile = argv[3];

    // check value of n: 0 < n <= 100
    if (n < 1 || n > 100)
    {
        fprintf(stderr, "n must be between 1 and 100\n");
        return 2;
    }

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    /* Varibles of the original image */
    int32_t biw = bi.biWidth;
    int32_t bih = bi.biHeight;
    int32_t scan = bi.biWidth * sizeof(RGBTRIPLE);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }

    /* Changing values for the resized image */
    int repeat_rows = 1; // flag for the counting of rows
    bi.biWidth = bi.biWidth*n;
    bi.biHeight = bi.biHeight*n;
    int32_t r_scan = bi.biWidth * sizeof(RGBTRIPLE);
    int r_padding = (4 - (r_scan) % 4) % 4;
    bi.biSizeImage = (r_scan + r_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int padding = (4 - (bi.biWidth/n * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bih*n); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < biw; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // repeat the same pixel k (= n) times over the scanline
            for (int px = 0; px < n; px++)
            {
                // write RGB triple to outfile
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        if (repeat_rows%n != 0)
        {
            // start again over the same row
            fseek(inptr, -scan, SEEK_CUR);
        }
        else
        {
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
        }

        // then add it back (to demonstrate how)
        for (int k = 0; k < r_padding; k++)
        {
            fputc(0x00, outptr);
        }

        repeat_rows++;
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
