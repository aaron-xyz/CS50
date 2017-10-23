"""
Pset6: Mario

From pset1 - mario (more)
imported from C to Python

$ python mario.py
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
"""

def main():
    # Request the height
    while True:
        height = int(input("Height: "))
        # height must between the interval [0,23]
        if height >= 0 and height < 24:
            break

    spaces = height
    blocks = 0

    # pyramid rows
    for i in range(height):

        # left pyramid (columns)
        for j in range(height):
            if j < spaces-1:
                print(" ", end="")
            else:
                print("#", end="")
                blocks += 1

        # Gap between pyramids
        print("  ", end="")

        # Right pyramid
        for k in range(height):
            if blocks > 0:
                print("#", end="")
            else:
                break
            blocks -= 1

        spaces -= 1
        print()


# execute the function caled main
if __name__ == "__main__":
    main()