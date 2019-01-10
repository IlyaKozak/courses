
# program that cracks
# anushree: 50xcIMJ0y.RXo -> YES (0 sec)
# brian: 50mjprEcqC/ts -> CA (0 sec)
# bjbrown: 50GApilQSG3E2 -> UPenn
# lloyd: 50n0AAUD.pL8g -> lloyd
# malan: 50CcfIk1QrPr6 -> maybe
# maria: 509nVI8B9VfuA -> TF (0 sec)
# natmelo: 50JIIyhDORqMU -> nope (10 sec)
# rob: 50JGnXUgaafgc -> ROFL
# stelios: 51u8F0dkeDSbY -> NO (0 sec)
# zamyla: 50cI2vYkF0YU2 -> LOL (0 sec)
import itertools
import string
import crypt
import sys
#import time

# program needs to accept a single command-line argument: a hashed password
if len(sys.argv) != 2:
    print("Usage: python crack.py hash")
    sys.exit(1)

#startTime = time.time()
hashedPass = sys.argv[1]
password = ""
# salt is the first 2 digits of a hashed password
salt = hashedPass[:2]


def crackPass(passwordLength):
    for s in itertools.product(string.ascii_letters, repeat=passwordLength):
        password = "".join(s)
        if crypt.crypt(password, salt) == hashedPass:
            print(password)
#            endTime = time.time() - startTime
#            print(int(endTime), "sec")
            sys.exit(0)


crackPass(1)
crackPass(2)
crackPass(3)
crackPass(4)
# crackPass(5)