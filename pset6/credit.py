"""
Pset6: Credit

From pset1 - credit
imported from C to Python

$ python credit
Number: 378282246310005
AMEX
"""

def main():
    # get the number
    numberCard = int(input("Number: "))

    # init some basic variables
    digits = []
    counter = 0
    even = 0
    odd = 0

    # checking the number digit by digit
    while numberCard != 0:
        # get the last digit
        lastDigit = numberCard % 10
        # store that digit
        digits.append(lastDigit)
        # truncate that las digit
        numberCard = numberCard // 10

        # even numbers are added
        if counter%2 == 0:
            even = even + lastDigit
        # odd numbers are multiplied by 2 and then added
        else:
            # the product has 2 digits
            if lastDigit*2 > 9:
                doubleDigit = lastDigit*2
                while doubleDigit != 0:
                    odd = odd + doubleDigit%10
                    doubleDigit = doubleDigit // 10
            # the product has 1 digit
            else:
                odd = odd + lastDigit*2
        counter += 1

    # last digit of addition must be zero
    addition = even + odd

    # Master Card or Visa of 16 digits
    if (counter == 16) and (addition%10 == 0):
        # is Master Card?
        if digits[15] == 5:
            for i in range(1,6):
                if digits[14] == i:
                    print("MASTERCARD")
                    break
        # is Visa?
        elif digits[15] == 4:
            print("VISA")
        # Not valid
        else:
            print("INVALID")

    # American Express
    elif (counter == 15) and (addition%10 == 0):
        if (digits[14] == 3) and (digits[13]==7 or digits[13]==4):
            print("AMEX")
        else:
            print("INVALID")

    # Visa of 13 digits
    elif (counter == 13) and (addition%10 == 0):
        if (digits[12] == 4):
            print("VISA")
        else:
            print("INVALID")

    # non-valid number
    else:
        print("INVALID")



if __name__ == "__main__":
    main()