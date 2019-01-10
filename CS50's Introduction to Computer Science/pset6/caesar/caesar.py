# program that encrypts messages using Caesar’s cipher
import sys

# program needs to accept a command-line argument, key
if len(sys.argv) != 2 or not sys.argv[1].isdigit():
    print("Usage: python caesar.py key")
    sys.exit(1)

key = int(sys.argv[1]) % 26
plaintext = input("plaintext: ")
ciphertext = ""

# Caesar "encrypts" confidential messages by shifting each letter therein by some number of places.
# For instance (if key = 1), A as B, B as C, C as D, …, and, wrapping around alphabetically, Z as A.
for c in plaintext:
    if c.isalpha():
        if c.islower():
            ciphertext += chr((ord(c) - ord("a") + key) % 26 + ord("a"))
        if c.isupper():
            ciphertext += chr((ord(c) - ord("A") + key) % 26 + ord("A"))
    else:
        ciphertext += c
print("ciphertext: ", ciphertext)