from random import randint


def is_valid(num):
    return num.isdigit()


num = randint(1, 100)
tries = 0
print('I made a number from 1 to 100 - guess it')

while True:
    n = input()
    if is_valid(n) and 1 <= int(n) <= 100:
        tries += 1
        if int(n) == num:
            print("That's it! Your tries:", tries)
            break
        elif int(n) < num:
            print('Try to choose a bigger one')
        elif int(n) > num:
            print('Try to choose a smaller one')
    else:
        tries += 1
        print('Try enter correctly')
