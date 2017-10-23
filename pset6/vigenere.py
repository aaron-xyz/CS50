"""
Pset6: Vigenere

From pset1 - vigenere
imported from C to Python

$ python vigenere.py ABC
plaintext:  HELLO
ciphertext: HFNLP

$ python vigenere.py bacon
plaintext: Meet me at the park at eleven am
ciphertext: Negh zf av huf pcfx bt gzrwep oz
"""
import sys
def main():
    # check correct number or inputs
    if len(sys.argv) != 2:
        print("You must enter the key: python vigenere.py KEY")
        exit(1)

    # every char must be alphabetical
    key = sys.argv[1]
    if (not key.isalpha()):
        print("k must be alpha: python vigenere.py k")
        exit(2)

    # input
    p = input("plaintext: ")
    c = ""
    j = 0
    lkey = len(key)

    # cipher the plaintext
    for char in p:

        # char is uppercase letter
        if char.isalpha() and char.isupper():
            # char of key is uppercase
            if key[j].isupper():
                shift = ( (ord(char)-ord('A')) + (ord(key[j])-ord('A')) )%26 + ord('A')
                c = c + chr(shift)
            else:
                shift = ( (ord(char)-ord('A')) + (ord(key[j])-ord('a')) )%26
                c = c + chr(shift + ord('A'))
            # next index for k
            j = (j+1) % lkey

        # char is lowercase letter
        elif char.isalpha() and char.islower():
            # char of key is lower
            if key[j].islower():
                shift = ( (ord(char)-ord('a')) + (ord(key[j])-ord('a')) )%26
                c = c + chr(shift + ord('a'))
            else:
                shift = ( (ord(char)-ord('a')) + (ord(key[j])-ord('A')) )%26
                c = c + chr(shift + ord('a'))
            # next index for k
            j = (j+1) % lkey

        # do not shift if char is not a letter
        else:
            c = c + char

    # print ciphered text
    print("ciphertext: {}".format(c))


if __name__ == "__main__":
    main()