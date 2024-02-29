#include <stdlib.h>

#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  char *buff = calloc(s21_strlen(str) + 1, sizeof(char));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] > 96 && str[i] < 123)
      buff[i] = str[i] - 32;
    else
      buff[i] = str[i];
  }
  buff[s21_strlen(str)] = '\0';
  return buff;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) return S21_NULL;
  char *buff = calloc(s21_strlen(str) + 1, sizeof(char));
  for (s21_size_t i = 0; i < s21_strlen(str); i++) {
    if (str[i] >= 'A' && str[i] <= 'Z')
      buff[i] = str[i] + 'a' - 'A';
    else
      buff[i] = str[i];
  }

  return buff;
}

// void rtrim(char *string, const char *trim) {
//   int i;
//   for (i = s21_strlen(string) - 1;
//        i >= 0 && s21_strchr(trim, string[i]) != NULL; i--) {
//     string[i] = '\0';
//   }
// }

// void ltrim(char *string, const char *trim) {
//   while (string[0] != '\0' && s21_strchr(trim, string[0]) != NULL) {
//     s21_memmove(&string[0], &string[1], s21_strlen(string));
//   }
// }

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src) return S21_NULL;
  if (!trim_chars || *trim_chars == '\0') trim_chars = " \n\b\t";
  int l = 0, r = s21_strlen(src) - 1, j = 0;
  for (; src[l] && s21_strchr(trim_chars, src[l]); l++) {
  }
  for (; l < r && s21_strchr(trim_chars, src[r]); r--) {
  }
  char *res = malloc(r - l + 2);
  if (res) {
    for (int i = l; i <= r; i++, j++) res[j] = src[i];
    res[j] = '\0';
  }
  return (void *)res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t lensrc = 0;
  s21_size_t lenstr = 0;

  if (src != S21_NULL)
    lensrc = s21_strlen(src);
  else
    lensrc = 0;
  if (str != S21_NULL)
    lenstr = s21_strlen(str);
  else
    lenstr = 0;

  s21_size_t len = lensrc + lenstr;

  if (start_index > lensrc) return S21_NULL;

  // char *res = (char *)malloc(len + 1);
  char *res = (char *)calloc(len + 1, sizeof(char));

  if (res) {
    for (s21_size_t i = 0; i < len; i++) {
      if (i < start_index)
        res[i] = src[i];
      else if (i < start_index + lenstr)
        res[i] = str[i - start_index];
      else
        res[i] = src[i - lenstr];
    }
  }
  res[lensrc + lenstr] = '\0';
  return (void *)res;
}

// int main() {
//   char *str5 = "1234567890abcdefghijklmnopqrstuvwxyz1234567890";
//   char *str6 = s21_to_upper((const char*) str5);
//   puts(str6);
// }