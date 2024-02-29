#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <math.h>
#include <stdarg.h>
#include <wchar.h>

#include "../s21_string.h"

enum {
  PLUS_SPEC = 0b00001,   // '+'
  MINUS_SPEC = 0b00010,  // '-'
  SPACE_SPEC = 0b00100,  // ' '
  HASH_SPEC = 0b01000,   // '#'
  ZERO_SPEC = 0b10000    // '0'
};

s21_size_t print_number_signed(char *str, long number, int precision);
s21_size_t print_number_unsigned(char *output, int base, unsigned long number,
                                 int precision, int uppercase);
s21_size_t print_number_float(char *output_string, long double input_number,
                              int precision, int keep_same_exp, int *exponent);
int get_degree(long double number);
s21_size_t print_number_float_e(char *buffer, char exponent_letter,
                                long double number, int precision);
void apply_width(char *output_string, s21_size_t *previous_output_length,
                 char *buffer, s21_size_t buffer_size, int format_flags,
                 int output_width);
int str_to_int_with_index(const char *str, int *index);
void parse_format_flags(const char *format_string, s21_size_t *prev_index,
                        int *flags, int *width, int *precision,
                        char *length_modifier);
int print_str_from_wstr(char *str, wchar_t *wstr);
#endif  // S21_SPRINTF_H
