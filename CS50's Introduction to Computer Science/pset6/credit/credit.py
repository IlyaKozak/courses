# program that determines whether a provided credit card number is valid according to Luhn’s algorithmzu
import sys

while True:
    number = input("Please enter your credit card number: ")
    if number.isdigit():
        break

# Luhn’s algorithm (if the card is valid)
# 0. Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.
# 1. Add the sum to the sum of the digits that weren’t multiplied by 2.
# 2. If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!

index = 0
num_sum = 0
for d in reversed(number):
    if index % 2 != 0:
        num_sum += (int(d) * 2) // 10
        num_sum += (int(d) * 2) % 10
    else:
        num_sum += int(d)
    index += 1

if num_sum % 10 != 0:
    print("INVALID")
    sys.exit(0)

# American Express numbers all start with 34 or 37
# American Express uses 15-digit numbers
if len(number) == 15 and int(number[0]) == 3 and (int(number[1]) == 4 or int(number[1]) == 7):
    print("AMEX")

# MasterCard numbers all start with 51, 52, 53, 54, or 55
# MasterCard uses 16-digit numbers
if len(number) == 16 and int(number[0]) == 5 and (int(number[1]) >= 1 and int(number[1]) <= 5):
    print("MASTERCARD")

# Visa numbers all start with 4
# Visa uses 13- and 16-digit numbers
if (len(number) == 13 or len(number) == 16) and int(number[0]) == 4:
    print("VISA")