def russian_cesar_cipher():
    string, k = input().lower(), int(input())
    cipher_list = []
    symbols = '!#$%&*+-=?@^_,. '
    if k == 0 or k == 32:
        cipher_list = list(string)
        return cipher_list
    elif k > 32:
        k %= 32

    for i in range(len(string)):
        if string[i] == 'ё':  # swap(е, ё)
            string[i] = 'e'

        if ord(string[i]) + k <= ord('я') and string[i] not in symbols:
            value_num = ord(string[i]) + k
            cipher_list.append(chr(value_num))
        elif string[i] not in symbols and k < 32:
            value_num = ord('а') - 1 + k - int(ord('я') - ord(string[i]))
            cipher_list.append(chr(value_num))
        else:
            cipher_list.append(string[i])

    return cipher_list


def english_cesar_cipher():
    string, k = input().lower(), int(input())
    cipher_list = []
    symbols = '!#$%&*+-=?@^_,. '
    if k == 0 or k == 26:
        cipher_list = list(string)
        return cipher_list
    elif k > 26:
        k %= 26

    for i in range(len(string)):
        if ord(string[i]) + k <= ord('z') and string[i] not in symbols:
            value_num = ord(string[i]) + k
            cipher_list.append(chr(value_num))
        elif string[i] not in symbols and k < 26:
            value_num = ord('a') - 1 + k - int(ord('z') - ord(string[i]))
            cipher_list.append(chr(value_num))
        else:
            cipher_list.append(string[i])

    return cipher_list


print('Выбери язык шифровки ([рус] - русский, [en] - english)')
while True:
    inp = input()
    if inp == 'рус':
        print('Введи строку на русском и ключ сдвига')
        russian_ciphered_list = russian_cesar_cipher()
        print(*russian_ciphered_list, sep='')
        break
    elif inp == 'en':
        print('Введи строку на английском и ключ сдвига')
        english_cphered_list = english_cesar_cipher()
        print(*english_cphered_list, sep='')
        break
    else:
        print('Выбери язык шифровки ([рус] - русский, [en] - english)')