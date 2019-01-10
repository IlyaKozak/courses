# program that calculates the minimum number of coins required to give a user change
from cs50 import get_float

# input float from a user
while True:
    change = get_float("Please enter your chage (float): ")
    if type(change) == float and change >= 0:
        break

# number of coins required to give a user change
count = 0
change = round(change * 100)

# number of quarters
count += change // 25
change %= 25
# number of dimes
count += change // 10
change %= 10
# number of nickels
count += change // 5
change %= 5
# number of pennies
count += change

print(count)