#ifndef SRC_sscanf_S21_SSCANF_H_
#define SRC_sscanf_S21_SSCANF_H_

#include <errno.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_string.h"
typedef unsigned long long ullong_type;
typedef long long llong_type;
#define S21_ULLONG_MAX (~(ullong_type)0)
#define S21_ULONG_MAX ((unsigned long)(~0L))      /* 0xFFFFFFFF */
#define S21_LONG_MAX ((long)(S21_ULONG_MAX >> 1)) /* 0x7FFFFFFF */
#define S21_LONG_MIN ((long)(~S21_LONG_MAX))      /* 0x80000000 */
#define S21_LLONG_MAX ((llong_type)(S21_ULLONG_MAX >> 1))

#define S21_LLONG_MIN (~S21_LLONG_MAX) /* 0x8000000000000000 */
#define flags_char "CcsS"
#define flags_int "diouxn"
#define flags_float "EeFfGgAa"
#define width_float "L"
#define width_int_char "h"
#define width_shared "l"
#define width_num "0123456789"

struct specif {
  char flag[4];
  char width[310];
  char precision[310];
  char length[3];
  char type;
};

enum type_flag {
  SHARED,
  CHAR_INT,
  CHAR_FLAG,
  INT_FLAG,
  FLOAT_FLAG,
};
long s21_strtol(const char *nptr, char **endptr, register int base);
unsigned long s21_strtoul(const char *nptr, char **endptr, register int base);
ullong_type s21_strtoull(const char *nptr, char **endptr, register int base);
llong_type s21_strtoll(const char *nptr, char **endptr, register int base);
long double s21_atold(char *str);
long long s21_atoll(const char *str);
long s21_atol(const char *str);
int s21_sscanf(const char *str, const char *format, ...);
void scanf_specifier_parsing(char *str, struct specif *spec);
void scanf_numbers_parsing(char *str, char *buff);
void scanf_pointer_shift(char **buff, char *buff1, const char *str);
void scanf_specifier_init(struct specif *spec);
int match_str_and_format(char *str, struct specif *spec, va_list *ap, int *j,
                         char c);
int check_falid_format(const char *format);
int s21_isspace(char c);
int read_d(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_s(char *str, va_list *ap, struct specif *spec, int *j);
int read_c(char *str, va_list *ap, struct specif *spec, int *j);
int read_u(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_o(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_xX(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_f(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_g(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_e(char *str, va_list *ap, struct specif *spec, int *j, char c);
int read_i(char *str, va_list *ap, struct specif *spec, int *j, char c);
int s21_isdigit(char c);
int s21_isupper(char c);
int s21_isalpha(char c);
int s21_empty_str(char *str);
// int s21_isunsigned(char c);
int s21_ishex(char c);
int s21_isoctal(char c);
#endif  // SRC_sscanf_s21_sscanf_H_