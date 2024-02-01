def find_all(list, symbol):
    return [i for i in range(len(list)) if list[i] == symbol]


def hangman():
    word = list(input())
    tries = 9
    true_letters_counter = 0

    while tries > 0:
        letter = input()
        if letter in word:
            iterator = len(find_all(word, letter))
            print('Буква находится в слове на месте:', find_all(word, letter))
            true_letters_counter += iterator
        else:
            print('Этой буквы в слове нет')
            tries -= 1
        print('Количество оставшихся попыток = ', tries)

        if tries == 0:
            print('Ты проиграл')
        elif true_letters_counter == len(word):
            print('Ты победил')
            break


# Вводи слова в нижнем регистре
hangman()
