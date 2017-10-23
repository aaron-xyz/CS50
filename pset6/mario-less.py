"""
Pset6: Mario (less)

From pset1 - mario (less)
imported from C to Python

$ python mario-less.py
Height: 4
   ##
  ###
 ####
#####
"""

def main():
    # get height
    while True:
        height = int(input("Height: "))
        # height must between the interval [0,23]
        if height >= 0 and height < 24:
            break

    spaces = height

    # print pyramid
    for r in range(height):
        spaces -= 1
        # create columns
        for c in range(height + 1):
            if c <= spaces - 1:
                print(" ", end="")
            else:
                print("#", end="")
        print()


# execute the function called main
if __name__ == "__main__":
    main()