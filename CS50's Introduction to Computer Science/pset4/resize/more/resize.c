// Copies a BMP file

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage - rogram should accept exactly three command-line arguments
    if (argc != 4)
    {
        fprintf(stderr, "Usage: copy infile outfile\n");
        return 1;
    }

    // f is resize factor (i.e., enlargement or shrinking) as a float
    float f = atof(argv[1]);

    // f must be a floating-point value in (0.0, 100.0]
    if (f <= 0 || f > 100)
    {
        fprintf(stderr, "The first argument in main must be a floating-point value in (0.0, 100.0]\n");
        return 1;
    }

    // pointers to input file and to output file
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

    // biWidth, biHeight  of infile
    int biWidth_in = bi.biWidth;
    int biHeight_in = bi.biHeight;

    // biWidth, biHeight of outfile
    bi.biWidth = round(bi.biWidth * f);
    bi.biHeight = round(bi.biHeight * f);

    // padding of infile
    int padding_in = (4 - (biWidth_in * sizeof(RGBTRIPLE)) % 4) % 4;
    // padding of outfile
    int padding_out = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // biSizeImage of outfile
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + padding_out) * abs(bi.biHeight);
    printf("%d  %d\n", biWidth_in, bi.biWidth);
    // biSize of outfile
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // temporary storage for infile scanline (buffer)
    RGBTRIPLE *buffer = malloc(bi.biWidth * sizeof(RGBTRIPLE));

    // tracker of pixels in temporary storage (buffer)
    int tracker;
    // tracker of rows written to outfile
    int tracker_rows = 0;

    // additional rows (if needed) to be added to outfile
    int add_row = abs(bi.biHeight % biHeight_in);

    // if resize factor f < 1, there is no additional rows
    if (abs(bi.biHeight) < abs(biHeight_in))
    {
        add_row = 0;
    }

    // going through infile rows
    for (int i = 0; i < abs(biHeight_in); i++)
    {
        tracker = 0;

        // additional pixels (if needed) to be added to temporary storage (buffer)
        int add_pix = bi.biWidth % biWidth_in;

        // if resize factor f < 1, there is no additional pixels
        if (bi.biWidth < biWidth_in)
        {
            add_pix = 0;
        }

        // going through infile pixels
        for (int j = 0; j < biWidth_in; j++)
        {

            // temporary storage for a pixel
            RGBTRIPLE triple;
            // reading RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // (f >= 1) adding pixels to temporary storage (buffer) times (int) f
            for (int k = 0; k < bi.biWidth / biWidth_in; k++)
            {
                *(buffer + tracker) = triple;
                tracker++;
            }

            // (f > 1) adding additional pixels to temporary storage (buffer) to fully pack it
            if (add_pix > 0)
            {
                *(buffer + tracker) = triple;
                tracker++;
                add_pix--;
            }

            // (f < 1) && omitting some infile pixels && not exceeding temporary storage
            if (bi.biWidth < biWidth_in && j % (biWidth_in / bi.biWidth) == 0 && tracker < bi.biWidth)
            {
                printf("%i %i\n ", j, tracker);
                *(buffer + tracker) = triple;
                tracker++;
            }

        }

        // (f >= 1) writing rows to outfile times (int) f
        for (int l = 0; l < bi.biWidth / biWidth_in; l++)
        {
            fwrite(buffer, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            for (int m = 0; m < padding_out; m++)
            {
                fputc(0x00, outptr);
            }

        }

        // (f > 1) writing additional rows to outfile to fully pack it
        if (add_row > 0)
        {
            fwrite(buffer, sizeof(RGBTRIPLE), bi.biWidth, outptr);

            for (int m = 0; m < padding_out; m++)
            {
                fputc(0x00, outptr);
            }
            add_row--;
        }

        // (f < 1)
        if (abs(bi.biHeight) < abs(biHeight_in))
        {
            // omitting some infile pixels && not exceeding outfile rows
            if (i % abs(biHeight_in / bi.biHeight) == 0 && tracker_rows < abs(bi.biHeight))
            {
                fwrite(buffer, sizeof(RGBTRIPLE), bi.biWidth, outptr);

                for (int m = 0; m < padding_out; m++)
                {
                    fputc(0x00, outptr);
                }
                tracker_rows++;
            }

        }

        // skip over infile padding, if any
        fseek(inptr, padding_in, SEEK_CUR);
    }

    // free buffer
    free(buffer);

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
