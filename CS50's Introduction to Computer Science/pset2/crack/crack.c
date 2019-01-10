/* Program that cracks passwords
name: Input (argv[1]) -> Output
anushree: 50xcIMJ0y.RXo -> YES
brian: 50mjprEcqC/ts -> CA
bjbrown: 50GApilQSG3E2 -> UPenn
lloyd: 50n0AAUD.pL8g -> lloyd
malan: 50CcfIk1QrPr6 -> maybe
maria: 509nVI8B9VfuA -> TF
natmelo: 50JIIyhDORqMU -> nope
rob: 50JGnXUgaafgc -> ROFL
stelios: 51u8F0dkeDSbY -> NO
zamyla: 50cI2vYkF0YU2 -> LOL
*/

#define _XOPEN_SOURCE
#include <unistd.h>

#include <cs50.h>
#include <stdio.h>
#include <string.h>


// Size of password (up to 5 digits)
#define PASS_SIZE 5

int main(int argc, string argv[])
{
// Program accepts a single command-line argument: a hashed password
    if (argc == 2)
    {
        string hash = argv[1];
        char salt[3];
        // Salt is the first 2 digits of a hashed password
        salt[0] = hash[0];
        salt[1] = hash[1];
        salt[2] = '\0';

        char password[6] = {'\0'};

        while (1)
        {
            // Generating a new password
            // Going from 'A' to 'Z' and from 'a' to 'z' for every digit
            int digit = 0;
            while (digit < PASS_SIZE)
            {
                if (password[digit] == 0)
                {
                    password[digit] = 'A';
                    break;
                }
                if (password[digit] >= 'A' && password[digit] < 'Z')
                {
                    password[digit]++;
                    break;
                }
                if (password[digit] == 'Z')
                {
                    password[digit] = 'a';
                    break;
                }
                if (password[digit] >= 'a' && password[digit] < 'z')
                {
                    password[digit]++;
                    break;
                }
                if (password[digit] == 'z')
                {
                    password[digit] = 'A';
                    digit++;
                }
            }

            // Breaking from the infinite while loop while (1) when we reached PASS_SIZE
            if (digit >= PASS_SIZE)
            {
                break;
            }

            // Hashing a generated password with C’s DES-based crypt function.
            string pass_hash = crypt(password, salt);
            // Check if a hash of a generated password equalts to the given hash (a command-line argument)
            if (strcmp(pass_hash, hash) == 0)
            {
                printf("%s\n", password);
                break;
            }
        }
        return 0;
    }
    else
    {
        printf("Error! Program accepts a single command-line argument: a hashed password!\n");
        return 1;
    }
}