# a program that prints out a half-pyramid of a specified height
from cs50 import get_int

# height is a non-negative integer no greater than 23
while True:
    height = get_int("Height: ")
    if height >= 0 and height <= 23:
        break

for row in range(height):
    count = height - row
    for c in range(height):
        if count > 1:
            print(" ", end="")
            count -= 1
        else:
            print("#", end="")
    print("#")