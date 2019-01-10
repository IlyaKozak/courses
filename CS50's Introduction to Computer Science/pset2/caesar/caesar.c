// Program that encrypts message using Caesar’s cipher
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check for a single command-line argument and a non-negative integer
    if (argc == 2 && atoi(argv[1]) >= 0)
    {
        string plaintext = get_string("plaintext: ");
        string ciphertext = plaintext;

        // Loop throught the plaintext string character by character
        for (int i = 0; i < strlen(plaintext); i++)
        {
            // Check if character is an alphabetic letter
            if (isalpha(plaintext[i]))
            {
                // Check if character is lowercase
                if (islower(plaintext[i]))
                {
                    // For lowercase: ASCII values ('a' is 97) to alphabetical indexes ("a" is 0).
                    // Caesar’s algorithm (i.e., cipher) encrypts messages by "rotating" each letter by k positions.
                    // c[i]=(p[i]+k)mod26
                    // atoi - convert a string to an integer
                    // Alphabetical indexes to ASCII values
                    ciphertext[i] = ((plaintext[i] - 97 + atoi(argv[1])) % 26 + 97);
                }
                else
                {
                    // For uppercase: ASCII values ('A' is 65) to alphabetical indexes ("A" is 0).
                    // Caesar's algorithm
                    // Alphabetical indexes to ASCII values
                    ciphertext[i] = ((plaintext[i] - 65 + atoi(argv[1])) % 26 + 65);
                }
            }
            else
            {
                // If character is not letter
                ciphertext[i] = plaintext[i];
            }
        }

        // Print of ciphertext and return 0
        printf("ciphertext: %s\n", ciphertext);
        return 0;
    }
    else
    {
        // If command-line check is not passed we print error message and return 1
        printf("Error: program accepts a single command-line argument, a non-negative integer.\n");
        return 1;
    }
}