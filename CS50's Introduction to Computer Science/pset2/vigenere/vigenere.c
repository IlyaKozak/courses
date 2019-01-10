// program that encrypts messages using Vigenère’s cipher
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Check for a command-line argument (key) which contains only alphabetical characters
    bool alpha = true;
    string key;
    if (argv[1])
    {
        key =  argv[1];
        for (int i = 0; i < strlen(key); i++)
        {
            if (!isalpha(key[i]))
            {
                alpha = false;
            }
        }
    }
    else
    {
        // If command-line check is not passed we print error message and return 1
        printf("Error: program accepts a single command-line argument, which contains only alphabetical characters.\n");
        return 1;
    }

    if (argc == 2 && alpha)
    {
        string plaintext = get_string("plaintext: ");
        string ciphertext = plaintext;

        // Loop throught the plaintext string character by character
        // j is counter for key indexes. Key upplies only to plaintext characters
        int j = 0;
        for (int i = 0; i < strlen(plaintext); i++)
        {
            // Check if character in plaintext is an alphabetic letter
            if (isalpha(plaintext[i]))
            {
                // Check if character in plaintext is lowercase
                if (islower(plaintext[i]))
                {
                    // For lowercase: ASCII values ('a' is 97) to alphabetical indexes ("a" is 0).
                    // Vigenère’s algorithm (i.e., cipher) encrypts messages using a sequence of keys.
                    // Vigenère’s keys A represents 0, B represents 1, C represents 2, …, and Z represents 25
                    // c[i]=(p[i]+k[j])mod26
                    // Alphabetical indexes to ASCII values
                    ciphertext[i] = ((plaintext[i] - 97 + (tolower(key[j % strlen(key)]) - 97)) % 26 + 97);
                    j++;
                }
                else
                {
                    // For uppercase: ASCII values ('A' is 65) to alphabetical indexes ("A" is 0).
                    // Vigenère’s algorithm
                    // Alphabetical indexes to ASCII values
                    ciphertext[i] = ((plaintext[i] - 65 + (tolower(key[j % strlen(key)]) - 97)) % 26 + 65);
                    j++;
                }
            }
            else
            {
                // If character in plaintext is not a letter
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
        printf("Error: program accepts a single command-line argument, which contains only alphabetical characters.\n");
        return 1;
    }
}