// Mario is climbing the full pyramid
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // User input "height of pyramid" is integer between 0 and 23.
    int height;
    do
    {
        height = get_int("Please enter a height of a full pyramid between 0 and 23: ");
    }
    while ((height < 0) || (height > 23));

    // Buidling the full pyramid with defined height using hashes and spaces.
    for (int i = 0; i < height; i++)
    {
        // Left-half of pyramid
        for (int j = height - (i + 1); j > 0; j--)
        {
            printf(" ");
        }
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        // The gap
        printf("  ");
        // Right-half of pyramid
        for (int l = 0; l < i + 1; l++)
        {
            printf("#");
        }

        printf("\n");
    }
}