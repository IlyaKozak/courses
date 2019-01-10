# program that encrypts messages using Vigenère’s cipher
import sys

# program needs to accept a command-line argument, keyword
if len(sys.argv) != 2 or not sys.argv[1].isalpha():
    print("Usage: python caesar.py keyword")
    sys.exit(1)

key = sys.argv[1].lower()
keyLenght = len(key)
plaintext = input("plaintext: ")
ciphertext = ""

# Vigenère’s cipher encryps messages using a sequence of keys (a keyword).
# (whereby A represents 0, B represents 1, C represents 2, …, and Z represents 25)
index = 0
for c in plaintext:
    if c.isalpha():
        if c.islower():
            ciphertext += chr((ord(c) - ord("a") + ord(key[index % keyLenght]) - ord("a")) % 26 + ord("a"))
            index += 1
        if c.isupper():
            ciphertext += chr((ord(c) - ord("A") + ord(key[index % keyLenght]) - ord("a")) % 26 + ord("A"))
            index += 1
    else:
        ciphertext += c
print("ciphertext:", ciphertext)