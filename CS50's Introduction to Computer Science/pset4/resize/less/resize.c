// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // n is a resize factor
    int n = atoi(argv[1]);

    // resize by a factor of n should be a positive integer less than or equal to 100
    if (n < 0 || n > 100)
    {
        fprintf(stderr, "Resize factor should be a positive integer less than or equal to 100\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // padding of infile
    int padding_in = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // biWidth of infile
    int biWidth_in = bi.biWidth;
    // biHeight of infile
    int biHeight_in = bi.biHeight;
    // biWidth of outfile
    bi.biWidth = bi.biWidth * n;
    // biHeight of outfile
    bi.biHeight = bi.biHeight * n;

    // padding of outfile
    int padding_out = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // biSizeImage of outfile
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi.biHeight);
    // biSize of outfile
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // resizing vertically
    for (int i = 0, biHeight = abs(biHeight_in); i < biHeight; i++)
    {
        // temporary storage
        RGBTRIPLE triple;

        // resizing horizontally for n-1
        for (int j = 0; j < n - 1; j++)
        {
            for (int k = 0; k < biWidth_in; k++)
            {
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // writing every pixel n-times to outfile
                for (int l = 0; l < n; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
            // write padding to outfile
            for (int m = 0; m < padding_out; m++)
            {
                fputc(0x00, outptr);
            }

            // sending infile cursor back
            fseek(inptr, -biWidth_in * sizeof(RGBTRIPLE), SEEK_CUR);
        }
        // resizing horizontally one more time
        for (int k = 0; k < biWidth_in; k++)
        {
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // writing every pixel n-times to outfile
            for (int l = 0; l < n; l++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }
        // write padding to outfile
        for (int m = 0; m < padding_out; m++)
        {
            fputc(0x00, outptr);
        }
        // skip over infile padding
        fseek(inptr, padding_in, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
