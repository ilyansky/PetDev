#include "grep.h"

void test_verdict(int *suc, int *fail, int comp, char diff[], char my_com[],
                  char com[]);

int array_counter(char *array[]) {
  int len = 0;
  while (array[len] != NULL) len++;
  return len;
}

void test_grep_utility();

int main() {
  test_grep_utility();

  return 0;
}

void test_grep_utility() {
  int suc = 0;
  int fail = 0;
  int comp = 0;
  int tests_am = 0;

  char my_com[1000] = "";
  char com[1000] = "";
  char diff[1000] = "diff custom_output.txt expected_output.txt > /dev/null";

  char flags[1000] = "eivclnhso";
  int flags_am = 9;

  char *patterns[] = {
      "H",           "char",    "\"Donec\"",
      "\"else if\"", "mark",    "\"Well, Watson, what do you make of it?\"",
      "nomatch",     "include", "{",
      "else",        "amount",  "fl",
      NULL};

  int patterns_am = array_counter(patterns);

  char *files[] = {"grep.c", "2.txt", "grep.h", "x.c", NULL};
  int files_am = array_counter(files);

  // Without flags, 1 file
  for (int i = 0; i < patterns_am; i++)
    for (int j = 0; j < files_am; j++) {
      tests_am++;
      sprintf(my_com, "./s21_grep %s %s &> custom_output.txt", patterns[i],
              files[j]);
      sprintf(com, "grep %s %s &> expected_output.txt", patterns[i], files[j]);
      printf("%d\n%s\n%s -> ", tests_am, com, my_com);
      test_verdict(&suc, &fail, comp, diff, my_com, com);
    }

  // Without flags, many files
  for (int i = 0; i < patterns_am; i++)
    for (int f1 = 0; f1 < files_am; f1++)
      for (int f2 = 0; f2 < files_am; f2++)
        for (int f3 = 0; f3 < files_am; f3++) {
          tests_am++;
          sprintf(my_com, "./s21_grep %s %s %s %s &> custom_output.txt",
                  patterns[i], files[f1], files[f2], files[f3]);
          sprintf(com, "grep %s %s %s %s &> expected_output.txt", patterns[i],
                  files[f1], files[f2], files[f3]);
          printf("%d\n%s\n%s -> ", tests_am, com, my_com);
          test_verdict(&suc, &fail, comp, diff, my_com, com);
        }

  // -e many 3/2 patterns, 1 file
  for (int i = 0; i < patterns_am - 2; i++)
    for (int j = 0; j < files_am; j++) {
      tests_am++;
      sprintf(my_com,
              "./s21_grep -e %s -e %s -e %s %s &> "
              "custom_output.txt",
              patterns[i], patterns[i + 1], patterns[i + 2], files[j]);
      sprintf(com, "grep -e %s -e %s -e %s %s &> expected_output.txt",
              patterns[i], patterns[i + 1], patterns[i + 2], files[j]);
      printf("%d\n%s\n%s -> ", tests_am, com, my_com);
      test_verdict(&suc, &fail, comp, diff, my_com, com);
    }

  for (int i = 0; i < patterns_am - 1; i++)
    for (int j = 0; j < files_am; j++) {
      tests_am++;
      sprintf(my_com,
              "./s21_grep -e %s -e %s %s &> "
              "custom_output.txt",
              patterns[i], patterns[i + 1], files[j]);
      sprintf(com, "grep -e %s -e %s %s &> expected_output.txt", patterns[i],
              patterns[i + 1], files[j]);
      printf("%d\n%s\n%s -> ", tests_am, com, my_com);
      test_verdict(&suc, &fail, comp, diff, my_com, com);
    }

  // -e many 3/2 patterns, many files
  for (int i = 0; i < patterns_am - 2; i++)
    for (int f1 = 0; f1 < files_am; f1++)
      for (int f2 = 0; f2 < files_am; f2++)
        for (int f3 = 0; f3 < files_am; f3++) {
          tests_am++;
          sprintf(my_com,
                  "./s21_grep -e %s -e %s -e %s %s %s %s &> "
                  "custom_output.txt",
                  patterns[i], patterns[i + 1], patterns[i + 2], files[f1],
                  files[f2], files[f3]);
          sprintf(com, "grep -e %s -e %s -e %s %s %s %s &> expected_output.txt",
                  patterns[i], patterns[i + 1], patterns[i + 2], files[f1],
                  files[f2], files[f3]);
          printf("%d\n%s\n%s -> ", tests_am, com, my_com);
          test_verdict(&suc, &fail, comp, diff, my_com, com);
        }
  for (int i = 0; i < patterns_am - 1; i++)
    for (int f1 = 0; f1 < files_am; f1++)
      for (int f2 = 0; f2 < files_am; f2++)
        for (int f3 = 0; f3 < files_am; f3++) {
          tests_am++;
          sprintf(
              my_com, "./s21_grep -e %s -e %s %s %s %s &> custom_output.txt",
              patterns[i], patterns[i + 1], files[f1], files[f2], files[f3]);
          sprintf(com, "grep -e %s -e %s %s %s %s &> expected_output.txt",
                  patterns[i], patterns[i + 1], files[f1], files[f2],
                  files[f3]);
          printf("%d\n%s\n%s -> ", tests_am, com, my_com);
          test_verdict(&suc, &fail, comp, diff, my_com, com);
        }

  // 1 file
  for (int i = 0; i < flags_am; i++)
    for (int j = 0; j < patterns_am; j++)
      for (int k = 0; k < files_am; k++) {
        tests_am++;
        sprintf(my_com, "./s21_grep -%c %s %s &> custom_output.txt", flags[i],
                patterns[j], files[k]);
        sprintf(com, "grep -%c %s %s &> expected_output.txt", flags[i],
                patterns[j], files[k]);
        printf("%d\n%s\n%s -> ", tests_am, com, my_com);
        test_verdict(&suc, &fail, comp, diff, my_com, com);
      }

  //   Many files
  for (int i = 0; i < flags_am; i++)
    for (int j = 0; j < patterns_am; j++)
      for (int f1 = 0; f1 < files_am; f1++)
        for (int f2 = 0; f2 < files_am; f2++)
          for (int f3 = 0; f3 < files_am; f3++) {
            tests_am++;
            sprintf(my_com, "./s21_grep -%c %s %s %s %s &> custom_output.txt",
                    flags[i], patterns[j], files[f1], files[f2], files[f3]);
            sprintf(com, "grep -%c %s %s %s %s &> expected_output.txt",
                    flags[i], patterns[j], files[f1], files[f2], files[f3]);
            printf("%d\n%s\n%s -> ", tests_am, com, my_com);
            test_verdict(&suc, &fail, comp, diff, my_com, com);
          }

  // f flag
  for (int i = 0; i < files_am; i++) {
    tests_am++;
    sprintf(my_com, "./s21_grep -f p.txt %s &> custom_output.txt", files[i]);
    sprintf(com, "grep -f p.txt %s &> expected_output.txt", files[i]);
    printf("%d\n%s\n%s -> ", tests_am, com, my_com);
    test_verdict(&suc, &fail, comp, diff, my_com, com);
  }

  for (int i = 0; i < files_am; i++) {
    tests_am++;
    sprintf(my_com, "./s21_grep -f x.txt %s &> custom_output.txt", files[i]);
    sprintf(com, "grep -f x.txt %s &> expected_output.txt", files[i]);
    printf("%d\n%s\n%s -> ", tests_am, com, my_com);
    test_verdict(&suc, &fail, comp, diff, my_com, com);
  }

  for (int f1 = 0; f1 < files_am; f1++)
    for (int f2 = 0; f2 < files_am; f2++)
      for (int f3 = 0; f3 < files_am; f3++) {
        tests_am++;
        sprintf(my_com, "./s21_grep -f p.txt %s %s %s &> custom_output.txt",
                files[f1], files[f2], files[f3]);
        sprintf(com, "grep -f p.txt %s %s %s &> expected_output.txt", files[f1],
                files[f2], files[f3]);
        printf("%d\n%s\n%s -> ", tests_am, com, my_com);
        test_verdict(&suc, &fail, comp, diff, my_com, com);
      }

  for (int f1 = 0; f1 < files_am; f1++)
    for (int f2 = 0; f2 < files_am; f2++)
      for (int f3 = 0; f3 < files_am; f3++) {
        tests_am++;
        sprintf(my_com, "./s21_grep -f p3.txt %s %s %s &> custom_output.txt",
                files[f1], files[f2], files[f3]);
        sprintf(com, "grep -f p3.txt %s %s %s &> expected_output.txt",
                files[f1], files[f2], files[f3]);
        printf("%d\n%s\n%s -> ", tests_am, com, my_com);
        test_verdict(&suc, &fail, comp, diff, my_com, com);
      }
  for (int f1 = 0; f1 < files_am; f1++)
    for (int f2 = 0; f2 < files_am; f2++)
      for (int f3 = 0; f3 < files_am; f3++) {
        tests_am++;
        sprintf(my_com, "./s21_grep -f p2.txt %s %s %s &> custom_output.txt",
                files[f1], files[f2], files[f3]);
        sprintf(com, "grep -f p2.txt %s %s %s &> expected_output.txt",
                files[f1], files[f2], files[f3]);
        printf("%d\n%s\n%s -> ", tests_am, com, my_com);
        test_verdict(&suc, &fail, comp, diff, my_com, com);
      }

  printf("\nSUCCESS: %d\n", suc);
  printf("FAIL: %d", fail);
}

void test_verdict(int *suc, int *fail, int comp, char diff[], char my_com[],
                  char com[]) {
  system(my_com);
  system(com);
  comp = system(diff);

  com[0] = '\0';
  my_com[0] = '\0';

  if (comp == 0) {
    (*suc)++;
    printf("SUCCESS\n");
  } else {
    (*fail)++;
    printf("FAIL\n");
  }
}
