#include <stdio.h>
#include <string.h>

void compress(char *str_old, char *str_new);

int main(void) {
    char str_old[101];
    char str_new[101];
    fgets(str_old, 101, stdin);
    fflush(stdin);
    compress(str_old, str_new);
    fputs(str_new, stdout);

    return (0);
}

void compress(char *str_old, char *str_new) {
    int ind = 0;
    int start = 1;
    for (int i = 0; str_old[i] != '\0'; i++) {
        if (str_old[i] == ' ' && start == 1) {
            if (str_old[i + 1] != ' ') {
                str_new[ind] = str_old[i + 1];
                start = 0;
            }
        }
        if (str_old[i] == ' ') {
            if (str_old[i + 1] != ' ' && str_old[i + 1] != '\n') {
                str_new[ind] = str_old[i];
                ind++;
            }
        } else if (str_old[i] != '\n') {
            str_new[ind] = str_old[i];
            ind++;
        }
    }

    if (str_new[0] == ' ')  // Remove first space
    {
        for (int i = 0; str_new[i] != '\0'; i++) str_new[i] = str_new[i + 1];
    }
}