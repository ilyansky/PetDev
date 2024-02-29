#include "cat.h"

int main(int amount, char *args[]) {
  struct Flags flag = {0, 0, 0, 0, 0, 0, 0, 0};

  int last_flag_ind =
      find_last_flag_ind(amount, args);  // Нахожу индекс последнего флага
  int check = flags_decompose(args, last_flag_ind, &flag);
  if (check != 0) {
    char s[10] = "";
    strcpy(s, args[check]);
    printf("cat: illegal option -- %c\nusage: cat [-belnstuv] [file ...]\n",
           s[1]);
  } else {
    for (int i = last_flag_ind + 1; i < amount; i++) cat(args[i], flag);
  }

  return 0;
}