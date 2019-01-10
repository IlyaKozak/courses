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
    int coins_count = 0;
    int coins = 0;

    // If change more than or = 25 cents, give quarters (25¢)
    if (change_owed / 25 >= 1)
    {
        coins = (change_owed - (change_owed % 25)) / 25;
        coins_count += coins;
        change_owed -= coins * 25;
    }

    // If change more than or = 10 cents, give dimes (10¢)
    if (change_owed / 10 >= 1)
    {
        coins = (change_owed - (change_owed % 10)) / 10;
        coins_count += coins;
        change_owed -= coins * 10;
    }

    // If change more than or = 5 cents, give nickels (5¢)
    if (change_owed / 5 >= 1)
    {
        coins = (change_owed - (change_owed % 5)) / 5;
        coins_count += coins;
        change_owed -= coins * 5;
    }

    // If change more than or = 1 cent, give pennies (1¢)
    if (change_owed / 1 >= 1)
    {
        coins = (change_owed - (change_owed % 1)) / 1;
        coins_count += coins;
        change_owed -= coins * 1;
    }

    // Printed total number of coins needed to give change
    printf("Total coins: %i\n", coins_count);
}