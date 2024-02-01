import random
import string


def generate_password(len):
    chars = list(
        '''0123456789!"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ''')
    random.shuffle(chars)
    password = ''
    for i in range(len):
        password += random.choice(chars)
    return password


len = int(input('Desired password length: '))
print(generate_password(len))
