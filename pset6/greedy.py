"""
Pset6: Greedy

From pset1 - greedy
imported from C to Python

$ python greedy.py
O hai! How much change is owed?
0.41
4
"""

def main():

    # Get change (in dollars)
    while True:
        # request amount
        owed = input("O hai! How much change is owed? ")
        # cast
        owed = float(owed)
        if (owed >= 0):
            break

    # get rid of decimal values and cast to int
    owed_int = int(100*owed)
    coins = 0

    # Get the minimum number of coins
    while owed_int > 0:
        # quarter
        if owed_int >= 25:
            owed_int -= 25
            coins += 1
        # dime
        elif owed_int >= 10:
            owed_int -= 10
            coins += 1
        # nickel
        elif owed_int >= 5:
            owed_int -= 5
            coins += 1
        # penny
        else:
            owed_int -= 1
            coins += 1

    # print the amount of coins
    print("{}".format(coins))

if __name__ == "__main__":
    main()