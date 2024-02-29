#include "s21_sprintf.h"

s21_size_t print_number_signed(char *str, long number, int precision) {
  char temp[100] = "";
  char digit_chars[] = "0123456789abcdef";
  s21_size_t count = 0;
  int is_negative = 0;

  if (number < 0) {
    number = -number;
    is_negative = 1;
  }

  do {
    temp[count++] = digit_chars[number % 10];
  } while (number /= 10);

  if (is_negative) {
    temp[count++] = '-';
  }

  int zero_padding = precision - count;
  if (zero_padding > 0) {
    s21_memset(&temp[count], '0', zero_padding);
    count += zero_padding;
  }

  for (int j = count - 1; j >= 0; j--) {
    str[count - 1 - j] = temp[j];
  }

  return count;
}

s21_size_t print_number_unsigned(char *output, int base, unsigned long number,
                                 int precision, int uppercase) {
  char digits[100] = "";
  char digit_chars[] = "0123456789abcdef";
  if (uppercase) s21_strcpy(digit_chars, "0123456789ABCDEF");

  s21_size_t digit_count = 0;
  do {
    digits[digit_count++] = digit_chars[number % base];
    number /= base;
  } while (number > 0);

  int zero_padding_count = precision - digit_count;
  for (int i = 0; i < zero_padding_count; i++) {
    digits[digit_count++] = '0';
  }

  for (int i = digit_count - 1; i >= 0; i--) {
    output[digit_count - 1 - i] = digits[i];
  }

  return digit_count;
}

s21_size_t print_number_float(char *output_string, long double input_number,
                              int precision, int keep_same_exp, int *degree) {
  char num_chars[] = "0123456789";
  s21_size_t output_length = 0;
  if (input_number < 0) {
    input_number = -input_number;
    output_string[output_length++] = '-';
  }
  s21_size_t start_index = output_length;
  int all_nines = 1;
  if (input_number == 0.0) {
    all_nines = 0;
    output_string[output_length++] = '0';
  } else {
    do {
      int digit_height = (int)trunc(log10(input_number));
      int digit_symbol = (int)trunc(input_number / pow(10, digit_height));
      output_string[output_length++] = num_chars[digit_symbol % 10];
      if (digit_symbol % 10 != 9) {
        all_nines = 0;
      }
      input_number -= digit_symbol * pow(10, digit_height);
    } while (input_number >= 1.0f);
  }
  if (precision < 0) {
    precision = 6;
  }
  s21_size_t dot_position = 0;
  if (precision > 0) {
    dot_position = output_length;
    output_string[output_length++] = '.';
    for (int j = -1; j >= -precision; j--) {
      int digit_symbol = (int)trunc(input_number / pow(10, j));
      output_string[output_length++] = num_chars[digit_symbol % 10];
      input_number -= digit_symbol * pow(10, j);
      if (digit_symbol % 10 != 9) {
        all_nines = 0;
      }
    }
  }
  double next_digit = trunc(input_number * pow(10, precision + 1));
  if (next_digit >= 5.0) {
    if (all_nines) {
      *degree += 1;
      output_string[start_index] = '1';
      for (s21_size_t j = start_index + 1; j < output_length + 1; j++) {
        output_string[j] = '0';
      }
      if (!keep_same_exp) {
        output_string[output_length++] = '0';
      }
      if (dot_position) {
        if (keep_same_exp) {
          output_string[dot_position] = '.';
        } else {
          output_string[dot_position + 1] = '.';
        }
      }
    } else {
      int stop = 0;
      for (s21_size_t j = output_length - 1; !stop && j >= start_index; j--) {
        if (output_string[j] != '.') {
          output_string[j] = (output_string[j] - '0' + 1) % 10 + '0';
          if (output_string[j] != '0') {
            stop = 1;
          }
        }
      }
    }
  }
  output_string[output_length] = '\0';

  return output_length;
}

int get_degree(long double number) {
  int degree = 0;
  if (number < 0) {
    number = -number;
  }
  while (number >= 10.0) {
    degree++;
    number /= 10;
  }
  while (0.0 < number && number < 1.0) {
    degree--;
    number *= 10;
  }
  return degree;
}

s21_size_t print_number_float_e(char *buffer, char exponent_letter,
                                long double number, int precision) {
  int degree = get_degree(number);
  number /= pow(10, degree);
  s21_size_t buffer_size =
      print_number_float(buffer, number, precision, 1, &degree);
  buffer[buffer_size++] = exponent_letter;
  if (degree < 0) {
    buffer[buffer_size++] = '-';
    degree = -degree;
  } else {
    buffer[buffer_size++] = '+';
  }
  if (degree < 10) {
    buffer[buffer_size++] = '0';
  }
  buffer_size += print_number_signed(buffer + buffer_size, degree, 1);
  buffer[buffer_size] = '\0';
  return buffer_size;
}

void apply_width(char *output_string, s21_size_t *previous_output_length,
                 char *buffer, s21_size_t buffer_size, int format_flags,
                 int output_width) {
  int output_string_length = *previous_output_length;
  int remaining_zeroes = output_width - buffer_size;
  int has_plus_sign = 0;

  if (format_flags & PLUS_SPEC) {
    if (buffer[0] != '-') {
      if (remaining_zeroes > 0 && !(format_flags & MINUS_SPEC)) {
        has_plus_sign = 1;
        remaining_zeroes--;
      } else {
        output_string[output_string_length++] = '+';
        remaining_zeroes--;
      }
    }
  }

  if ((format_flags & SPACE_SPEC) && !(format_flags & PLUS_SPEC)) {
    if (buffer[0] != '-') {
      output_string[output_string_length++] = ' ';
      remaining_zeroes--;
    }
  }

  if (remaining_zeroes > 0) {
    if (format_flags & MINUS_SPEC) {
      s21_memcpy(output_string + output_string_length, buffer, buffer_size);
      output_string_length += buffer_size;
      for (int i = 0; i < remaining_zeroes; i++) {
        output_string[output_string_length++] = ' ';
      }
    } else {
      char padding_char = ' ';
      char *temporary_buffer = buffer;
      if (format_flags & ZERO_SPEC) {
        padding_char = '0';
      }
      if (buffer[0] == '-' && (format_flags & ZERO_SPEC)) {
        output_string[output_string_length++] = '-';
        buffer_size--;
        temporary_buffer++;
      }
      for (int i = 0; i < remaining_zeroes; i++) {
        output_string[output_string_length++] = padding_char;
      }
      if (has_plus_sign) {
        output_string[output_string_length++] = '+';
      }
      output_string[output_string_length] = '\0';
      s21_memcpy(output_string + output_string_length, temporary_buffer,
                 buffer_size);
      output_string_length += buffer_size;
    }
  } else {
    s21_memcpy(output_string + output_string_length, buffer, buffer_size);
    output_string_length += buffer_size;
  }

  *previous_output_length = output_string_length;
}

int str_to_int_with_index(const char *str, int *index) {
  int result = 0;
  while (str[*index] >= '0' && str[*index] <= '9') {
    result = result * 10 + str[(*index)++] - '0';
  }
  return result;
}

void parse_format_flags(const char *format_string, s21_size_t *prev_index,
                        int *flags, int *width, int *precision,
                        char *length_modifier) {
  int index = *prev_index;
  index++;
  while (format_string[index] == '+' || format_string[index] == '-' ||
         format_string[index] == ' ' || format_string[index] == '#' ||
         format_string[index] == '0') {
    switch (format_string[index]) {
      case '+': {
        index++;
        *flags |= PLUS_SPEC;
        break;
      }
      case '-': {
        index++;
        *flags |= MINUS_SPEC;
        break;
      }
      case ' ': {
        index++;
        *flags |= SPACE_SPEC;
        break;
      }
      case '#': {
        index++;
        *flags |= HASH_SPEC;
        break;
      }
      case '0': {
        index++;
        *flags |= ZERO_SPEC;
        break;
      }
    }
  }
  if (format_string[index] >= '0' && format_string[index] <= '9') {
    *width = str_to_int_with_index(format_string, &index);
  } else if (format_string[index] == '*') {
    index++;
    *width = -1;
  }
  if (format_string[index] == '.') {
    index++;
    if (format_string[index] >= '0' && format_string[index] <= '9') {
      *precision = str_to_int_with_index(format_string, &index);
    } else if (format_string[index] == '*') {
      *precision = -1;
      index++;
    } else {
      *precision = 0;
    }
  }
  switch (format_string[index]) {
    case 'h': {
      *length_modifier = 'h';
      index++;
      break;
    }
    case 'l': {
      *length_modifier = 'l';
      index++;
      break;
    }
    case 'L': {
      *length_modifier = 'L';
      index++;
      break;
    }
  }
  *prev_index = index;
}

int print_str_from_wstr(char *dest, wchar_t *src) {
  int str_index = 0;
  int wchar_index = 0;
  int bytes_written = 0;
  do {
    str_index += bytes_written;
    bytes_written = wcrtomb(&dest[str_index], src[wchar_index++], NULL);
  } while (dest[str_index]);
  return str_index;
}

int s21_sprintf(char *str, const char *format, ...) {
  va_list ap;
  va_start(ap, format);
  s21_size_t format_len = s21_strlen(format), str_len = 0;
  int error = 0;
  *str = '\0';
  for (s21_size_t i = 0; !error && i < format_len; i++) {
    if (format[i] == '%') {
      int flags = 0;
      char length = 0;
      int width = 0, precision = -2;
      char buf[1024] = "";
      int buf_s = 0;
      parse_format_flags(format, &i, &flags, &width, &precision, &length);
      if (width == -1) width = va_arg(ap, int);
      if (precision == -1) precision = va_arg(ap, int);
      switch (format[i]) {
        case 'c': {
          char tmp_buf[9] = {0};
          int tmp_buf_s = 0;
          if (length == 'l') {
            wchar_t arg[2] = {0};
            arg[0] = va_arg(ap, wchar_t);
            tmp_buf_s = print_str_from_wstr(tmp_buf, arg);
          } else {
            tmp_buf[0] = va_arg(ap, int);
            tmp_buf_s = 1;
          }
          int zero_c = width - tmp_buf_s;
          char del = ' ';
          if (flags & ZERO_SPEC) del = '0';
          if (zero_c > 0 && !(flags & MINUS_SPEC)) {
            for (int j = 0; j < zero_c; j++) str[str_len++] = del;
            for (int j = 0; j < tmp_buf_s; j++) str[str_len++] = tmp_buf[j];
          } else if (flags & MINUS_SPEC) {
            for (int j = 0; j < tmp_buf_s; j++) str[str_len++] = tmp_buf[j];
            for (int j = 0; j < zero_c; j++) str[str_len++] = del;
          } else {
            for (int j = 0; j < tmp_buf_s; j++) str[str_len++] = tmp_buf[j];
          }
          break;
        }
        case 'i':
        case 'd': {
          long number;
          if (length == 'h') {
            number = (short)va_arg(ap, int);
          } else if (length == 'l') {
            number = va_arg(ap, long);
          } else {
            number = va_arg(ap, int);
          }
          if (precision || number) {
            buf_s = print_number_signed(buf, number, precision);
          } else {
            buf_s = 0;
          }
          buf[buf_s] = '\0';
          apply_width(str, &str_len, buf, buf_s, flags, width);
          break;
        }
        case 'e':
        case 'E': {
          long double number;
          if (length == 'L') {
            number = va_arg(ap, long double);
          } else {
            number = va_arg(ap, double);
          }
          buf_s = print_number_float_e(buf, format[i], number, precision);
          apply_width(str, &str_len, buf, buf_s, flags, width);
          break;
        }
        case 'f': {
          long double number;
          if (length == 'L') {
            number = va_arg(ap, long double);
          } else {
            number = va_arg(ap, double);
          }
          int trash_var = 0;
          buf_s = print_number_float(buf, number, precision, 0, &trash_var);
          apply_width(str, &str_len, buf, buf_s, flags, width);
          break;
        }
        case 'g':
        case 'G': {
          long double number;
          if (length == 'L') {
            number = va_arg(ap, long double);
          } else {
            number = va_arg(ap, double);
          }
          int degree = 0;
          int new_precision =
              precision - (int)trunc(log10(number > 0 ? number : -number) + 1);
          if (new_precision < 0) {
            new_precision = precision;
          }
          buf_s = print_number_float(buf, number, new_precision, 0, &degree);
          if (s21_strchr(buf, '.')) {
            while (buf[buf_s - 1] == '0') {
              buf_s--;
            }
            if (buf[buf_s - 1] == '.') {
              buf_s--;
            }
            buf[buf_s] = '\0';
          }
          char tmp_buf[1024];
          char e_letter;
          if (format[i] == 'G') {
            e_letter = 'E';
          } else {
            e_letter = 'e';
          }
          int tmp_buf_s =
              print_number_float_e(tmp_buf, e_letter, number, precision - 1);
          if (tmp_buf_s < buf_s) {
            apply_width(str, &str_len, tmp_buf, tmp_buf_s, flags, width);
          } else {
            apply_width(str, &str_len, buf, buf_s, flags, width);
          }
          break;
        }
        case 'o': {
          unsigned long number;
          if (length == 'h') {
            number = (unsigned short)va_arg(ap, unsigned int);
          } else if (length == 'l') {
            number = va_arg(ap, unsigned long);
          } else {
            number = va_arg(ap, unsigned int);
          }
          buf_s = print_number_unsigned(buf, 8, number, precision, 0);
          int zero_c = width - buf_s;
          if (!(buf[0] == '0' && !(flags & HASH_SPEC) && precision == 0)) {
            if (buf[0] == '0') flags &= ~HASH_SPEC;
            if (flags & HASH_SPEC) zero_c -= 1;
            if (zero_c > 0) {
              if (flags & MINUS_SPEC) {
                if (flags & HASH_SPEC) str[str_len++] = '0';
                s21_memcpy(str + str_len, buf, buf_s);
                str_len += buf_s;
                for (int j = 0; j < zero_c; j++) str[str_len++] = ' ';
              } else {
                char del = ' ';
                if (flags & ZERO_SPEC) del = '0';
                for (int j = 0; j < zero_c; j++) str[str_len++] = del;
                if (flags & HASH_SPEC) str[str_len++] = '0';
                s21_memcpy(str + str_len, buf, buf_s);
                str_len += buf_s;
              }
            } else {
              if (flags & HASH_SPEC) str[str_len++] = '0';
              s21_memcpy(str + str_len, buf, buf_s);
              str_len += buf_s;
            }
          }
          break;
        }
        case 's': {
          char *arg = S21_NULL;
          int arg_n = 0;
          int set_free = 0;
          if (length == 'l') {
            arg_n = print_str_from_wstr(&str[str_len], va_arg(ap, wchar_t *));
            arg = (char *)malloc(arg_n + 1);
            s21_strcpy(arg, &str[str_len]);
            set_free = 1;
            str[str_len] = '\0';
          } else {
            arg = va_arg(ap, char *);
            arg_n = s21_strlen(arg);
          }
          int zero_c = width - arg_n;
          char del = ' ';
          if (flags & ZERO_SPEC) del = '0';
          if (zero_c > 0 && !(flags & MINUS_SPEC)) {
            for (int j = 0; j < zero_c; j++) str[str_len++] = del;
            s21_memcpy(str + str_len, arg, arg_n);
            str_len += arg_n;
          } else if (flags & MINUS_SPEC) {
            s21_memcpy(str + str_len, arg, arg_n);
            str_len += arg_n;
            for (int j = 0; j < zero_c; j++) str[str_len++] = del;
          } else {
            s21_memcpy(str + str_len, arg, arg_n);
            str_len += arg_n;
          }
          if (set_free) free(arg);
          break;
        }
        case 'u': {
          unsigned long number;
          if (length == 'h') {
            number = (unsigned short)va_arg(ap, unsigned int);
          } else if (length == 'l') {
            number = va_arg(ap, unsigned long);
          } else {
            number = va_arg(ap, unsigned int);
          }
          if (flags & SPACE_SPEC) flags &= ~SPACE_SPEC;
          if (flags & PLUS_SPEC) flags &= ~PLUS_SPEC;
          if (precision || number) {
            buf_s = print_number_unsigned(buf, 10, number, precision, 0);
          } else {
            buf_s = 0;
          }
          buf[buf_s] = '\0';
          apply_width(str, &str_len, buf, buf_s, flags, width);
          break;
        }
        case 'X':
        case 'x':
        case 'p': {
          unsigned long number;
          if (format[i] == 'x') {
            if (length == 'l')
              number = va_arg(ap, unsigned long);
            else
              number = va_arg(ap, unsigned);
          } else if (format[i] == 'X') {
            if (length == 'l')
              number = va_arg(ap, unsigned long);
            else
              number = va_arg(ap, unsigned);
          } else {
            number = (unsigned long)va_arg(ap, void *);
          }
          if (precision || number) {
            buf_s = print_number_unsigned(buf, 16, number, precision,
                                          format[i] == 'X' ? 1 : 0);
          } else {
            buf_s = 0;
          }
          buf[buf_s] = '\0';
          int zero_c = width - buf_s;
          if (buf_s > 0) {
            if ((flags & HASH_SPEC) || format[i] == 'p') {
              zero_c -= 2;
            }
            if ((flags & SPACE_SPEC) && !(flags & PLUS_SPEC)) {
              if (buf[0] != '-') {
                str[str_len++] = ' ';
                zero_c--;
              }
            }
            if (zero_c > 0) {
              if (flags & MINUS_SPEC) {
                if ((flags & HASH_SPEC) || format[i] == 'p') {
                  str[str_len++] = '0';
                  if (format[i] == 'X')
                    str[str_len++] = 'X';
                  else
                    str[str_len++] = 'x';
                }
                s21_memcpy(str + str_len, buf, buf_s);
                str_len += buf_s;
                for (int j = 0; j < zero_c; j++) str[str_len++] = ' ';
              } else {
                char del = ' ';
                char *tm = buf;
                if (flags & ZERO_SPEC) del = '0';
                if (del == '0') {
                  if ((flags & HASH_SPEC) || format[i] == 'p') {
                    str[str_len++] = '0';
                    if (format[i] == 'X')
                      str[str_len++] = 'X';
                    else
                      str[str_len++] = 'x';
                  }
                  for (int j = 0; j < zero_c; j++) str[str_len++] = del;
                } else {
                  for (int j = 0; j < zero_c; j++) str[str_len++] = del;
                  if ((flags & HASH_SPEC) || format[i] == 'p') {
                    str[str_len++] = '0';
                    if (format[i] == 'X')
                      str[str_len++] = 'X';
                    else
                      str[str_len++] = 'x';
                  }
                }
                str[str_len] = '\0';
                s21_memcpy(str + str_len, tm, buf_s);
                str_len += buf_s;
              }
            } else {
              if ((flags & HASH_SPEC) || format[i] == 'p') {
                str[str_len++] = '0';
                if (format[i] == 'X')
                  str[str_len++] = 'X';
                else
                  str[str_len++] = 'x';
              }
              s21_memcpy(str + str_len, buf, buf_s);
              str_len += buf_s;
            }
          }
          break;
        }
        case 'n': {
          int *arg = va_arg(ap, int *);
          *arg = str_len;
          break;
        }
        case '%': {
          str[str_len++] = '%';
          break;
        }
        default: {
          error = 1;
        }
      }
    } else {
      str[str_len++] = format[i];
    }
  }
  str[str_len] = '\0';
  va_end(ap);
  return (int)str_len;
}
