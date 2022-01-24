from cs50 import get_float

coins = 0

# ask for an input of change in dollar
while True:
    dollar = get_float("Input Change in dollars ($): ")
    if dollar > 0:
        break

# convert dollar into cents then round
cents = round(int(dollar * 100))

# add coint till dollar change is zero
while cents > 0:
    # add 1 quarter coin if dollar is greater than or equal to 25
    while cents >= 25:
        coins += 1
        cents -= 25
    # add 1 dime coin if dollar is greater than or equal 10
    while cents >= 10:
        coins += 1
        cents -= 10
    # add 1 nickels coin if dollar is greater than or equal 15
    while cents >= 5:
        coins += 1
        cents -= 5
    # add 1 Pennie coin if dollar is greater than or equal 1
    while cents >= 1:
        cents -= 1
        coins += 1
print(coins)
