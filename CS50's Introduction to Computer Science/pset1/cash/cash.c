// Program that calculates the minimum number of coins required to give a user change.
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // User input of change (positive float)
    float change;
    do
    {
        change = get_float("Change owed: ");
    }
    while (change < 0);

    // Change in cents: float to int multiplied by 100 and rounded to the nearest integer number
    int change_owed = round(change * 100);
    int coins = 0;

    // If change more than or = 25 cents, give quarters (25¢)
    while (change_owed >= 25)
    {
        change_owed -= 25;
        coins++;
    }

    // If change more than or = 10 cents, give dimes (10¢)
    while (change_owed >= 10)
    {
        change_owed -= 10;
        coins++;
    }

    // If change more than or = 5 cents, give nickels (5¢)
    while (change_owed >= 5)
    {
        change_owed -= 5;
        coins++;
    }

    // If change more than or = 1 cent, give pennies (1¢)
    while (change_owed >= 1)
    {
        change_owed -= 1;
        coins++;
    }

    // Printed total number of coins needed to give change
    printf("Total coins: %i\n", coins);
}