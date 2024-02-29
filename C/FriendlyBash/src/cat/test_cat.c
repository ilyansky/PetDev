#include "cat.h"

int main() {
  test_cat_utility();

  return 0;
}

void test_cat_utility() {
  int suc = 0;
  int fail = 0;
  int compare;

  char flags[] = "benstv";
  char custom_com[100];
  char com[100];
  char diff[100] = "diff custom_output.txt expected_output.txt > /dev/null";

  // Тесты на одиночные флаги
  for (int i = 0; i < (int)strlen(flags); i++) {
    sprintf(custom_com, "./s21_cat -%c 1.txt > custom_output.txt", flags[i]);
    sprintf(com, "cat -%c 1.txt > expected_output.txt", flags[i]);

    command_launcher(custom_com, com);
    compare = system(diff);
    printf("Flag = %c ", flags[i]);
    counter(compare, &suc, &fail);
  }

  // Тесты на 5 флагов
  sprintf(custom_com, "./s21_cat -e -n -s -t -v 1.txt > custom_output.txt");
  sprintf(com, "cat -e -n -s -t -v 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = e n s t v ");
  counter(compare, &suc, &fail);
  //
  sprintf(custom_com, "./s21_cat -b -n -s -t -v 1.txt > custom_output.txt");
  sprintf(com, "cat -b -n -s -t -v 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = b n s t v ");
  counter(compare, &suc, &fail);
  //
  sprintf(custom_com, "./s21_cat -b -e -s -t -v 1.txt > custom_output.txt");
  sprintf(com, "cat -b -e -s -t -v 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = b e s t v ");
  counter(compare, &suc, &fail);
  //
  sprintf(custom_com, "./s21_cat -b -e -n -t -v 1.txt > custom_output.txt");
  sprintf(com, "cat -b -e -n -t -v 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = b e n t v ");
  counter(compare, &suc, &fail);
  //
  sprintf(custom_com, "./s21_cat -b -e -n -s -v 1.txt > custom_output.txt");
  sprintf(com, "cat -b -e -n -s -v 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = b e n s v ");
  counter(compare, &suc, &fail);
  //
  sprintf(custom_com, "./s21_cat -b -e -n -s -t 1.txt > custom_output.txt");
  sprintf(com, "cat -b -e -n -s -t 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = b e n s t ");
  counter(compare, &suc, &fail);
  ////

  // Тесты на смежные флаги
  for (int i = 0; i < (int)strlen(flags); i++)
    for (int j = 0; j < (int)strlen(flags); j++)
      for (int k = 0; k < (int)strlen(flags); k++)
        for (int h = 0; h < (int)strlen(flags); h++) {
          if ((i != j && i != k && i != h) && (j != k && j != h) && (k != h)) {
            sprintf(custom_com, "./s21_cat -%c%c%c%c 1.txt > custom_output.txt",
                    flags[i], flags[j], flags[k], flags[h]);
            sprintf(com, "cat -%c%c%c%c 1.txt > expected_output.txt", flags[i],
                    flags[j], flags[k], flags[h]);

            command_launcher(custom_com, com);
            compare = system(diff);
            printf("Flag = %c%c%c%c ", flags[i], flags[j], flags[k], flags[h]);
            counter(compare, &suc, &fail);
          }
        }

  // Тесты на несколько файлов
  for (int i = 0; i < (int)strlen(flags); i++)
    for (int j = 0; j < (int)strlen(flags); j++)
      for (int k = 0; k < (int)strlen(flags); k++) {
        if ((i != j && i != k) && (j != k)) {
          sprintf(custom_com,
                  "./s21_cat -%c%c%c 1.txt 1.txt > custom_output.txt", flags[i],
                  flags[j], flags[k]);
          sprintf(com, "cat -%c%c%c 1.txt 1.txt > expected_output.txt",
                  flags[i], flags[j], flags[k]);

          command_launcher(custom_com, com);
          compare = system(diff);
          printf("Flag = %c %c %c ", flags[i], flags[j], flags[k]);
          counter(compare, &suc, &fail);
        }
      }

  // Тест на отсутствие флагов
  sprintf(custom_com, "./s21_cat 1.txt 1.txt > custom_output.txt");
  sprintf(com, "cat 1.txt 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Without flag ");
  counter(compare, &suc, &fail);

  // Тесты GNU флагов
  //--number-nonblank
  sprintf(custom_com, "./s21_cat --number-nonblank 1.txt > custom_output.txt");
  sprintf(com, "cat -b 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = --number-nonblank ");
  counter(compare, &suc, &fail);

  //--number
  sprintf(custom_com, "./s21_cat --number 1.txt > custom_output.txt");
  sprintf(com, "cat -n 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = --number ");
  counter(compare, &suc, &fail);

  //--squeeze-blank
  sprintf(custom_com, "./s21_cat --squeeze-blank 1.txt > custom_output.txt");
  sprintf(com, "cat -s 1.txt > expected_output.txt");

  command_launcher(custom_com, com);
  compare = system(diff);
  printf("Flag = --squeeze-blank ");

  counter(compare, &suc, &fail);

  printf("SUCCESS: %d\n", suc);
  printf("FAIL: %d", fail);
}

void counter(int compare, int *suc, int *fail) {
  if (compare == 0) {
    (*suc)++;
    printf("SUCCESS\n");
  } else {
    (*fail)++;
    printf("FAIL\n");
  }
}

void command_launcher(char custom_com[], char com[]) {
  system(custom_com);
  system(com);
}