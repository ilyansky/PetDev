#include "cat.h"

// Main func
void cat(char filename[], struct Flags flag) {
  FILE *file = fopen(filename, "r");

  if (file == NULL) {
    printf("cat: %s: No such file or directory\n", filename);
    return;
  }

  char line[300];
  int streak_null_lines = 0, not_empty_counter = 0, pre_ne_counter = 0,
      count = 0;

  while (fgets(line, 300, file)) {
    if (flag.s) {
      int indic = s_f(line, &streak_null_lines);
      if (indic == 0) continue;
      // Если строка пустая больше 1 раза в ряд - функция возвратит 0
    }
    if (flag.e) {
      e_f(line);
    } else if (flag.E) {
      E_f(line);
    }

    if (flag.t) {
      t_f(line);
    } else if (flag.T) {
      T_f(line);
    }

    if (flag.v) {
      char temp[300] = "";
      for (int i = 0; i < (int)strlen(line); i++) v_f(line[i], temp);
      line[0] = '\0';
      strcpy(line, temp);
    }

    if (flag.b) {
      b_f(line, &not_empty_counter, &pre_ne_counter, flag);
    }
    if (flag.n) {
      n_f(&count);
    }

    // Вывод строки
    if (flag.b) {  // Предыдущий каунтер == текущему
      if (not_empty_counter != pre_ne_counter)
        printf("%6d\t%s", not_empty_counter, line);
      else if (flag.e || flag.E)
        printf("%s", line);
      else
        printf("%s", line);
    } else if (flag.n) {
      printf("%6d\t%s", count, line);
    } else {
      printf("%s", line);
    }
    // Здесь отрабатываются случаи: без флагов n и b, флагов нет
  }

  fclose(file);
}

// Sup funcs
int check_flag_correct(char option[]) {
  int res = 0;

  if (strcmp(option, "-b") != 0 && strcmp(option, "--number-nonblank") != 0 &&
      strcmp(option, "-e") != 0 && strcmp(option, "-E") != 0 &&
      strcmp(option, "-n") != 0 && strcmp(opt]]ion, "--number") != 0 &&
      strcmp(option, "-s") != 0 && strcmp(option, "--squeeze-blank") != 0 &&
      strcmp(option, "-t") != 0 && strcmp(option, "-T") != 0 &&
      strcmp(option, "-v") != 0) {
    res = 1;
  }
  return res;
}

int flags_decompose(char *args[], int last_flag_ind, struct Flags *flag) {
  int res = 0;
  for (int i = 1; i <= last_flag_ind; i++) {
    if (strlen(args[i]) > 2 && strlen(args[i]) < 7)
    // Флаг составной
    {
      char composite_option[10];
      strcpy(composite_option, args[i]);
      for (int j = 1; j < (int)strlen(args[i]); j++) {
        char option[10];
        optn[0] = '-';
        option[1] = composite_option[j];
        if (check_flag_correct(option)) {
          res = j;
          break;
        }
        flag_detector(flag, option);
      }
    } else  // Флаг не составной
    {
      if (check_flag_correct(
              args[i])) {  // Если флага не существует - функция возвратит 1 и
                           // программа остановится (см. main)
        res = i;
        break;
      }
      flag_detector(flag, args[i]);
    }
  }

  return res;
}

void flag_detector(struct Flags *flag, char option[]) {
  if (strcmp(option, "-b") == 0 || strcmp(option, "--number-nonblank") == 0)
    flag->b = 1;
  if (strcmp(option, "-n") == 0 || strcmp(option, "--number") == 0) flag->n = 1;
  if (strcmp(option, "-s") == 0 || strcmp(option, "--squeeze-blank") == 0)
    flag->s = 1;
  if (strcmp(option, "-e") == 0) flag->e = 1;
  if (strcmp(option, "-E") == 0) flag->E = 1;
  if (strcmp(option, "-t") == 0) flag->t = 1;
  if (strcmp(option, "-T") == 0) flag->T = 1;
  if (strcmp(option, "-v") == 0) flag->v = 1;
}

int find_last_flag_ind(int amount, char *args[]) {
  regex_t regex;
  int reti;

  reti = regcomp(&regex, "-", 0);
  if (reti) {
    printf("Failed to compile regex");
    return 0;
  }

  int last_flag_ind = 0;
  for (int i = 1; i < amount; i++) {
    reti = regexec(&regex, args[i], 0, NULL, 0);
    if (reti == 0) {
      last_flag_ind++;
    } else if (reti != REG_NOMATCH) {
      printf("Error while executing regex");
    }
  }

  regfree(&regex);
  return last_flag_ind;
}

// Flags
int s_f(char line[], int *streak_null_lines) {
  int indic = 0;
  if (*streak_null_lines == 0 && strcmp(line, "\n") == 0) {
    *streak_null_lines = 1;
    indic = 1;
  } else if (*streak_null_lines && strcmp(line, "\n") != 0) {
    *streak_null_lines = 0;
    indic = 1;
  } else if (strcmp(line, "\n") != 0) {
    indic = 1;
  }
  return indic;
}

void e_f(char line[]) {
  char temp[300] = "";
  for (int i = 0; i < (int)strlen(line); i++) {
    if (line[i] == '\n') {
      strcat(temp, "$\n");
    } else if (line[i] != '\t') {  // Если символ не таб - вызов флага v_f
      v_f(line[i], temp);
    } else {
      strcat(temp, "\t");
    }
  }
  line[0] = '\0';
  strcpy(line, temp);
}

void E_f(char line[]) {
  char temp[300] = "";
  char temp2[300] = "";
  for (int i = 0; i < (int)strlen(line); i++) {
    if (line[i] == '\n') {
      strcat(temp, "$\n");
    } else {
      int check = snprintf(temp2, sizeof(temp2), "%s%c", temp, line[i]);
      if (check >= (int)sizeof(temp2)) return;
      strcpy(temp, temp2);
    }
  }

  line[0] = '\0';
  strcpy(line, temp);
}

void v_f(char sym, char temp[]) {
  char temp2[300] = "";
  if (sym == 127) {
    strcat(temp, "^?");
  } else if (isascii(sym) == 0) {
    strcat(temp, "M-");
  } else if (iscntrl(sym) && sym != 127 && sym != '\n' && sym != '\t') {
    strcat(temp, "^");
    sym += 64;
    // Конкатенация строки и символа
    int check = snprintf(temp2, sizeof(temp2), "%s%c", temp, sym);
    if (check >= (int)sizeof(temp2)) return;
    strcpy(temp, temp2);

  } else {
    int check = snprintf(temp2, sizeof(temp2), "%s%c", temp, sym);
    if (check >= (int)sizeof(temp2)) return;
    strcpy(temp, temp2);
  }
}

void t_f(char line[]) {
  char temp[300] = "";
  for (int i = 0; i < (int)strlen(line); i++) {
    if (line[i] == '\t') {
      strcat(temp, "^I");
    } else {
      v_f(line[i], temp);
    }
  }
  line[0] = '\0';
  strcpy(line, temp);
}

void T_f(char line[]) {
  char temp[300] = "";
  char temp2[300] = "";
  for (int i = 0; i < (int)strlen(line); i++) {
    if (line[i] == '\t') {
      strcat(temp, "^I");
    } else {
      int check = snprintf(temp2, sizeof(temp2), "%s%c", temp, line[i]);
      if (check >= (int)sizeof(temp2)) return;
      strcpy(temp, temp2);
    }
  }
  line[0] = '\0';
  strcpy(line, temp);
}

void b_f(char line[], int *not_empty_counter, int *pre_not_empty_counter,
         struct Flags flag) {
  *pre_not_empty_counter = *not_empty_counter;

  if (flag.e || flag.E) {  // Если есть флаг е или Е - пустую строчку считаем $
    if (strcmp(line, "$\n") != 0) {
      (*not_empty_counter)++;
    }
  } else {  // Если флага е или Е нет - пустая строчка \n
    if (line[0] != '\n') {
      (*not_empty_counter)++;
    }
  }
}

void n_f(int *count) { (*count)++; }
