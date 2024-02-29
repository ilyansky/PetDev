#include "../s21_string.h"

#include "s21_strerror.h"

char msg_str[32];

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *s = (const unsigned char *)str;
  char *res = S21_NULL;
  s21_size_t i = 0;
  while (res == S21_NULL && i < n) {
    if (s[i] == c) res = (void *)s + i;
    i++;
  }
  return res;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  if (n == 0) return 0;
  const char *s1 = (const char *)str1;
  const char *s2 = (const char *)str2;
  s21_size_t i = 0;
  while (i < n - 1 && s1[i] == s2[i]) i++;
  return s1[i] - s2[i];
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *dest_s = (unsigned char *)dest;
  const unsigned char *src_s = (const unsigned char *)src;
  for (s21_size_t i = 0; i < n; i++) dest_s[i] = src_s[i];
  return dest_s;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *s = (unsigned char *)str;
  for (s21_size_t i = 0; i < n; i++) {
    s[i] = c;
  }
  return s;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t dest_l = s21_strlen(dest);
  for (s21_size_t i = 0; src[i] != '\0' && i < n; i++)
    dest[dest_l + i] = src[i];
  dest[dest_l + s21_strlen(dest)] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *res = S21_NULL;
  s21_size_t i = 0;
  if (c == '\0')
    res = "\0";
  else {
    while (str[i] != '\0' && res == S21_NULL) {
      if (str[i] == c) res = (char *)&str[i];
      i++;
    }
  }
  return res;
}

int s21_strcmp(const char *str1, const char *str2) {
  for (; *str2 && *str1 && (*str1 == *str2); str1++, str2++) {
  }
  return *str1 - *str2;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int i = 0;
  int res = 0;
  for (; *str1 && *str1 == *str2 && i < (int)n - 1; str1++, str2++) {
    i++;
  }
  if ((!*str1 && !*str2) || (n == 0))
    res = 0;
  else
    res = *str1 - *str2;
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  s21_size_t i, len = s21_strlen(src);
  for (i = 0; i <= len; i++) dest[i] = src[i];
  return dest;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t i, len = s21_strlen(src);
  for (i = 0; i <= len && i < n; i++) dest[i] = src[i];
  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t i = 0;
  for (; !s21_strchr(str2, str1[i]) && str1[i]; i++) {
  }
  return i;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t i;
  for (i = 0; str[i] != '\0'; i++) {
  }
  return i;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = S21_NULL;
  if (s21_strcspn(str1, str2) != s21_strlen(str1) && *str1 != '\0')
    res = (char *)str1 + s21_strcspn(str1, str2);
  return res;
}

char *s21_strrchr(const char *str, int c) {
  char *res = S21_NULL;
  s21_size_t len = s21_strlen(str);

  for (int i = len; i >= 0; i--) {
    if (str[i] == c) {
      res = ((char *)str) + i;
      break;
    }
  }

  return res;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t i = 0, j = 0;
  char *res = S21_NULL;
  do {
    j = 0;
    while (haystack[i] == needle[j] && needle[j] != '\0') {
      j++;
      i++;
    }
    if (needle[j] == '\0') {
      res = (char *)haystack + i - j;
      break;
    }
  } while (haystack[i++] != '\0');
  return res;
}

char *s21_strtok(char *str, const char *delim) {
  static char *input = S21_NULL;
  char *ret = S21_NULL;
  if (str != S21_NULL) {
    input = str;
  }
  if (input != S21_NULL) {
    s21_size_t delim_len = s21_strlen(delim);
    int stop = 0;
    while (!stop && *input) {
      int is_found_delim = 0;
      for (s21_size_t i = 0; !is_found_delim && *input && i < delim_len; i++) {
        if (*input == delim[i]) {
          is_found_delim = 1;
        }
      }
      if (!is_found_delim) {
        stop = 1;
      } else {
        input++;
      }
    }
    stop = 0;
    if (*input) {
      ret = input;
    }
    while (!stop && *input) {
      int is_found_delim = 0;
      for (s21_size_t i = 0; !is_found_delim && *input && i < delim_len; i++) {
        if (*input == delim[i]) {
          is_found_delim = 1;
          stop = 1;
          *input = '\0';
        }
      }
      input++;
    }
    if (!*input) {
      input = S21_NULL;
    }
  }
  return ret;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t i;
  for (i = 0; str1[i] && s21_strchr(str2, str1[i]); i++) {
  }
  return i;
}

char *s21_strerror(int errnum) {
  char *flag;
  if (!ERRLAST) {
    flag = "Unsupported OS";
  } else if (errnum > 0 && errstr[errnum - 1] && errnum - 1 < ERRLAST) {
    flag = errstr[errnum - 1];
  } else if (!errnum) {
    flag = "Undefined error: 0";
  } else {
    s21_sprintf(msg_str, "Unknown error: %d", errnum);
    flag = msg_str;
  }
  return flag;
}

int s21_atoi(char *str) {
  long long res = 0, sign = 1;
  if (*str == '-') {
    sign = -1;
    str++;
  }
  while (*str == ' ') str++;
  while ((*str > 47) && (*str < 58) && *str) {
    if (res >= INT16_MAX) return sign == -1 ? 0 : -1;
    res = res * 10 + (int)*str - 48;
    str += 1;
  }
  res *= sign;
  return res;
}
