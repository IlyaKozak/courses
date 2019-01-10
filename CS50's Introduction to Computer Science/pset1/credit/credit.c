// Program that determines whether a provided credit card number is valid according to Luhn’s algorithm.
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // Input from the user -> card number.
    long long int card_number;
    do
    {
        card_number = get_long_long(" Your credit card number:");
    }
    while (card_number < 0);

    // digit -> first number of the card,
    // digit 2 -> the second one,
    // count -> quantity of card numbers,
    // sum -> sum of the card's numbers according to Luhn’s algorithm.
    int digit, digit2;
    int count = 0;
    int sum = 0;
    while (card_number)
    {
        digit = card_number % 10;
        if (card_number >= 10)
        {
            digit2 = digit;
        }
        card_number /= 10;
        count++;

        if ((count % 2) == 0)
        {
            if (2 * digit >= 10)
            {
                sum += (2 * digit % 10) + 1;
            }
            else
            {
                sum += 2 * digit;
            }
        }
        else
        {
            sum += digit;
        }
    }

    // The last digit of the sum is a 0, so the card is legit!
    if (sum % 10 == 0)
    {
        // American Express uses 15-digit numbers. AMEX numbers all start with 34 or 37
        if ((count == 15) && (digit == 3) && ((digit2 == 4) || (digit2 == 7)))
        {
            printf("AMEX\n");
        }
        // MasterCard uses 16-digit numbers. MasterCard numbers all start with 51, 52, 53, 54, or 55
        else if ((count == 16) && (digit == 5) && (digit2 <= 5) && (digit2 >= 1))
        {
            printf("MASTERCARD\n");
        }
        // Visa uses 13- and 16-digit numbers. Visa numbers all start with 4
        else if (((count == 16) || (count == 13)) && (digit == 4))
        {
            printf("VISA\n");
        }
        // Otherwise the card in invalid
        else
        {
            printf("INVALID\n");
        }
    }
    // Otherwise the card in invalid
    else
    {
        printf("INVALID\n");
    }
}