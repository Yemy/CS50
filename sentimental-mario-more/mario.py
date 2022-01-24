from cs50 import get_int

while True:
    n = get_int("height: ")
    if n > 0 and n < 9:
        break

# loop to handle number of rows
for i in range(n):
    # k no of spaces
    k = 1
    # loop to handle spaces
    for k in range(n - i - 1):
        print(" ", end="")
    # loop to handle number of columns
    for j in range(i+1):
        # printing #
        print("#", end="")
    # print 2 spaces
    print("  ", end="")
    # print right mario #
    for y in range(i+1):
        print("#", end="")

    print()
