#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// A BYTE is an 8-bit unsigned value that corresponds to a single octet in a network protocol (unsigned char)
// A UINT8 is an 8-bit unsigned integer (range: 0 through 255 decimal).
// Because a UINT8 is unsigned, its first bit (Most Significant Bit (MSB)) is not reserved for signing.
typedef uint8_t BYTE;

// "Block size" is 512 bytes (B)
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Program should accept exactly one command-line argument, the name of a forensic image from which to recover JPEGs (card.raw)
    if (argc != 2)
    {
        fprintf(stderr, "Program accepts one command-line argument: the name of a forensic image from which to recover JPEGs (card.raw)\n");
        return 1;
    }

    // Open the input file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // File pointer to image-file
    FILE *img;

    // Temporary storage for one block of 512 B (buffer)
    BYTE buffer[BLOCK_SIZE];
    // Filename for image-files in format ###.jpg, where ### is three-digit decimal number from 000 on up
    char filename[8];
    // Tracker for number of image-files
    int tracker = 0;

    // Read until end of file (block is less than 512 B)
    while (fread(buffer, BLOCK_SIZE, 1, inptr) == 1)
    {
        // Checking for JPEG "signature": the first three bytes are 0xff 0xd8 0xff
        // The forth one is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, of 0xef.
        // Put another way, the fourth byte’s first four bits are 1110.
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // close image-files. At tracker = 0 there is no open image-file.
            if (tracker != 0)
            {
                fclose(img);
            }
            // Generating string for filename in format ###.jpg, where ### is three-digit decimal number from 000 on up
            sprintf(filename, "%03i.jpg", tracker);
            // The last char of the string is NUL
            filename[7] = '\0';
            // Tracker for number of image-files goes up by 1 for every opened file
            tracker++;
            // Open image-file
            img = fopen(filename, "w");
            if (img == NULL)
            {
                fprintf(stderr, "Could not open %s.\n", filename);
                return 3;
            }
        }

        // At tracker = 0 there is no open image-file.
        if (tracker != 0)
        {
            // Write buffer to image file
            fwrite(buffer, BLOCK_SIZE, 1, img);
        }
    }

    // Close the last image-file
    fclose(img);
    // Close input file
    fclose(inptr);
    // Success
    return 0;
}


