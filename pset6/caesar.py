"""
Pset6: Caesar

From pset1 - caesar
imported from C to Python

$ python caesar.py 13
plaintext:  HELLO
ciphertext: URYYB
"""
import sys
def main():
    # check correct number of arguments
    if len(sys.argv) != 2:
        print("You must enter the key: python caesar.py KEY")
        exit(1)

    key = int(sys.argv[1])
    p = input("plaintext: ")
    c = ""

    # cipher the plaintext
    for char in p:
        # is a letter - shift
        if char.isalpha():
            # is uppercase
            if char.isupper():
                shift = ( (ord(char) - ord('A') + key)%26 ) + ord('A')
                c = c + chr(shift)
            # is lowercase
            elif char.islower():
                shift = ( (ord(char) - ord('a') + key)%26 ) + ord('a')
                c = c + chr(shift)
        # do not change the caracter
        else:
            c = c + char

    # print ciphered string
    print("ciphered: {}".format(c))


if __name__ == "__main__":
    main()
