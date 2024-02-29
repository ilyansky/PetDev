#include "s21_sprintf_tests.h"

START_TEST(test_s21_sprintf) {
  char buff[500];
  char buff_right[500];

  char *format;
  int right;
  int out;

  format = "hello, %c !";
  //  buff_right = "hello, r !";
  right = sprintf(buff_right, format, 'r');
  out = s21_sprintf(buff, format, 'r');
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%c'!";
  //  buff_right = "hello, 'r'!";
  right = sprintf(buff_right, format, 'r', 149);
  out = s21_sprintf(buff, format, 'r', 149);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%4.0c'!";
  right = sprintf(buff_right, format, 'r');
  out = s21_sprintf(buff, format, 'r');
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%d'!";
  //  buff_right = "hello, '115'!";
  right = sprintf(buff_right, format, 115);
  out = s21_sprintf(buff, format, 115);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%d'!";
  //  buff_right = "hello, '-119'!";
  right = sprintf(buff_right, format, -119);
  out = s21_sprintf(buff, format, -119);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%05d'!";
  //  buff_right = "hello, '00003'!";
  right = sprintf(buff_right, format, 3);
  out = s21_sprintf(buff, format, 3);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%-05d'!";
  //  buff_right = "hello, '3    '!";
  right = sprintf(buff_right, format, 3);
  out = s21_sprintf(buff, format, 3);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%-+05d'!";
  //  buff_right = "hello, '+3   '!";
  right = sprintf(buff_right, format, 3);
  out = s21_sprintf(buff, format, 3);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%u'!";
  //  buff_right = "hello, '3'!";
  right = sprintf(buff_right, format, 3);
  out = s21_sprintf(buff, format, 3);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%u'!";
  //  buff_right = "hello, '4294967290'!";
  right = sprintf(buff_right, format, -6);
  out = s21_sprintf(buff, format, -6);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%05u'!";
  //  buff_right = "hello, '00005'!";
  right = sprintf(buff_right, format, 5);
  out = s21_sprintf(buff, format, 5);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '% 5u'!";
  //  buff_right = "hello, '    5'!";
  right = sprintf(buff_right, format, 5);
  out = s21_sprintf(buff, format, 5);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%%'!";
  //  buff_right = "hello, '%'!";
  right = sprintf(buff_right, format, 9);
  /*  9 --- без этого sprintf может стать целью эксплойта.
   *      ****тебе следует защититься от этого
   */
  out = s21_sprintf(buff, format);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%s'!";
  //  buff_right = "hello, 'A Telegram'!";
  right = sprintf(buff_right, format, "A Telegram");
  out = s21_sprintf(buff, format, "A Telegram");
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%lu'!";
  right = sprintf(buff_right, format, 99999999199);
  out = s21_sprintf(buff, format, 99999999199);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%080u'!";
  right = sprintf(buff_right, format, 4);
  out = s21_sprintf(buff, format, 4);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%08f'!";
  right = sprintf(buff_right, format, 2.13);
  out = s21_sprintf(buff, format, 2.13);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%-03f'!";
  right = sprintf(buff_right, format, -8.16);
  out = s21_sprintf(buff, format, -8.16);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%-09f'!";
  right = sprintf(buff_right, format, -8.16);
  out = s21_sprintf(buff, format, -8.16);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%p' and also '%d'!";
  right = sprintf(buff_right, format, &right, 112);
  out = s21_sprintf(buff, format, &right, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%20p' and also '%d'!";
  right = sprintf(buff_right, format, &right, 112);
  out = s21_sprintf(buff, format, &right, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%e' and also '%d'!";
  right = sprintf(buff_right, format, 45.98, 112);
  out = s21_sprintf(buff, format, 45.98, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%e' and also '%d'!";
  right = sprintf(buff_right, format, 56.97, 1);
  out = s21_sprintf(buff, format, 56.97, 1);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%E' and also '%d'!";
  right = sprintf(buff_right, format, 45.98, 112);
  out = s21_sprintf(buff, format, 45.98, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%*.*E' and also '%d'!";
  right = sprintf(buff_right, format, 9, 3, 45.98, 112);
  out = s21_sprintf(buff, format, 9, 3, 45.98, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%*x' and also '%d'!";
  right = sprintf(buff_right, format, 9, 14, 112);
  out = s21_sprintf(buff, format, 9, 14, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%#*x' and also '%d'!";
  right = sprintf(buff_right, format, 9, 14, 112);
  out = s21_sprintf(buff, format, 9, 14, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%*X' and also '%d'!";
  right = sprintf(buff_right, format, 9, 14, 112);
  out = s21_sprintf(buff, format, 9, 14, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%#*X' and also '%d'!";
  right = sprintf(buff_right, format, 9, 14, 112);
  out = s21_sprintf(buff, format, 9, 14, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%o' and also '%d'!";
  right = sprintf(buff_right, format, -9, 112);
  out = s21_sprintf(buff, format, -9, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%#*o' and also '%d'!";
  right = sprintf(buff_right, format, 9, 14, 112);
  out = s21_sprintf(buff, format, 9, 14, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  int hint = 0;
  int hint_right;

  format = "hello, '%o' %n*hinted* and also '%d'!";
  hint_right = 12;
  right = sprintf(buff_right, format, 9, &hint, 112);
  out = s21_sprintf(buff, format, 9, &hint, 112);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(hint_right, hint);
  ck_assert_int_eq(right, out);

  format = "hello, '%g' and also '%d'!";
  right = sprintf(buff_right, format, 56.97, 1);
  out = s21_sprintf(buff, format, 56.97, 1);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "hello, '%g' and also '%d'!";
  right = sprintf(buff_right, format, 0.097, 1);
  out = s21_sprintf(buff, format, 0.097, 1);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "%#05x";
  right = sprintf(buff_right, format, 21);
  out = s21_sprintf(buff, format, 21);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "%f";
  right = sprintf(buff_right, format, 6.5);
  out = s21_sprintf(buff, format, 6.5);
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "heelo %c 325";
  right = sprintf(buff_right, format, '\0');
  out = s21_sprintf(buff, format, '\0');
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);

  format = "heelo \0%c 325";
  right = sprintf(buff_right, format, 'b');
  out = s21_sprintf(buff, format, 'b');
  ck_assert_str_eq(buff_right, buff);
  ck_assert_int_eq(right, out);
}
END_TEST

START_TEST(simple_f) {
  char str1[100];
  char str2[100];
  double d = 1.0;
  char format[] = "!%f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(simple_Lf) {
  char str1[100];
  char str2[100];
  long double d = 1.0;
  char format[] = "!%Lf!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(negative_f) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!%f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(equal_precision) {
  char str1[100];
  char str2[100];
  double d = 1.312;
  char format[] = "!%.3f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(more_precision) {
  char str1[100];
  char str2[100];
  double d = 1.312;
  char format[] = "!%.6f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(zero_precision) {
  char str1[100];
  char str2[100];
  double d = 1.312;
  char format[] = "!%.0f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_and_precision) {
  char str1[100];
  char str2[100];
  double d = 1.312;
  char format[] = "!%3.2f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(width_and_precision_with_big_number) {
  char str1[100];
  char str2[100];
  double d = 1244121.312;
  char format[] = "!%3.2f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(only_width_with_small) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!%3f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flag_plus) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!%+f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(flag_space) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!% f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!%30f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_zero) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!%030f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_plus) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!%+30f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_plus_minus) {
  char str1[100];
  char str2[100];
  double d = 1.00000001;
  char format[] = "!%+-30f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_zero_minus_neg) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!%-030f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_neg) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!%30f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_zero_neg) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!%030f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_plus_neg) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!%+30f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_space_neg) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!% f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(big_width_space_plus) {
  char str1[100];
  char str2[100];
  double d = -1.00000001;
  char format[] = "!% +f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(round_precision) {
  char str1[100];
  char str2[100];
  double d = 3.1235;
  char format[] = "!%.3f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(round_with_nine) {
  char str1[100];
  char str2[100];
  double d = 3.1299;
  char format[] = "!%.3f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(round_all_nines) {
  char str1[100];
  char str2[100];
  double d = 9.9999;
  char format[] = "!%.3f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(zero_number) {
  char str1[100];
  char str2[100];
  double d = 0.0;
  char format[] = "!%.3f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(zero_precision_with_all_nines) {
  char str1[100];
  char str2[100];
  double d = 9.99;
  char format[] = "!%.0f!";
  sprintf(str1, format, d);
  s21_sprintf(str2, format, d);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(simple_x) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_n) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%x!\n";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_flags1) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%-x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_flags4) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%020x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_flags5) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%020x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_flags6) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%-020x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_flags9) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!% 20x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

END_TEST

START_TEST(simple_x_with_castom_width) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%*x!";
  sprintf(str1, tmp, 25, num);
  s21_sprintf(str2, tmp, 25, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_castom_length) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%0*hx!";
  sprintf(str1, tmp, 25, num);
  s21_sprintf(str2, tmp, 25, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_castom_length2) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%0*lx!";
  sprintf(str1, tmp, 25, num);
  s21_sprintf(str2, tmp, 25, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_xrecision) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%.25x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_xrecision_minus) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%.25x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_castom_xrecision) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%.*x!";
  sprintf(str1, tmp, 20, num);
  s21_sprintf(str2, tmp, 20, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_with_castom_xrecision_and_flags) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  char tmp[] = "!%25.*x!";
  sprintf(str1, tmp, 20, num);
  s21_sprintf(str2, tmp, 20, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_wiht_hash1) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%#x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_wiht_hash2) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%#.25x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_wiht_hash3) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%#25x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_wiht_hash4) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%-#25x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_wiht_hash5) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%-#.25x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_wiht_hash6) {
  char str1[100];
  char str2[100];
  unsigned long num = 1024;
  ;
  char tmp[] = "!%-#x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

START_TEST(simple_x_zero_precision_zero_number) {
  char str1[100];
  char str2[100];
  unsigned long num = 0;
  ;
  char tmp[] = "!%#.0x!";
  sprintf(str1, tmp, num);
  s21_sprintf(str2, tmp, num);
  ck_assert_pstr_eq(str1, str2);
}
END_TEST

Suite *s21_sprintf_test(void) {
  Suite *s = suite_create("s21_sprintf tests");
  TCase *tc = tcase_create("SPRINTF TESTS");
  suite_add_tcase(s, tc);
  tcase_add_test(tc, test_s21_sprintf);
  tcase_add_test(tc, simple_f);
  tcase_add_test(tc, simple_Lf);
  tcase_add_test(tc, negative_f);
  tcase_add_test(tc, equal_precision);
  tcase_add_test(tc, more_precision);
  tcase_add_test(tc, zero_precision);
  tcase_add_test(tc, width_and_precision);
  tcase_add_test(tc, width_and_precision_with_big_number);
  tcase_add_test(tc, only_width_with_small);
  tcase_add_test(tc, flag_plus);
  tcase_add_test(tc, flag_space);
  tcase_add_test(tc, big_width);
  tcase_add_test(tc, big_width_zero);
  tcase_add_test(tc, big_width_plus);
  tcase_add_test(tc, big_width_plus_minus);
  tcase_add_test(tc, big_width_zero_minus_neg);
  tcase_add_test(tc, big_width_neg);
  tcase_add_test(tc, big_width_zero_neg);
  tcase_add_test(tc, big_width_plus_neg);
  tcase_add_test(tc, big_width_space_neg);
  tcase_add_test(tc, big_width_space_plus);
  tcase_add_test(tc, round_precision);
  tcase_add_test(tc, round_with_nine);
  tcase_add_test(tc, round_all_nines);
  tcase_add_test(tc, zero_number);
  tcase_add_test(tc, zero_precision_with_all_nines);
  tcase_add_test(tc, simple_x);
  tcase_add_test(tc, simple_x_with_n);
  tcase_add_test(tc, simple_x_with_flags1);
  tcase_add_test(tc, simple_x_with_flags4);
  tcase_add_test(tc, simple_x_with_flags5);
  tcase_add_test(tc, simple_x_with_flags6);
  tcase_add_test(tc, simple_x_with_flags9);
  tcase_add_test(tc, simple_x_with_castom_width);
  tcase_add_test(tc, simple_x_with_castom_length);
  tcase_add_test(tc, simple_x_with_castom_length2);
  tcase_add_test(tc, simple_x_with_xrecision);
  tcase_add_test(tc, simple_x_with_xrecision_minus);
  tcase_add_test(tc, simple_x_with_castom_xrecision);
  tcase_add_test(tc, simple_x_with_castom_xrecision_and_flags);
  tcase_add_test(tc, simple_x_wiht_hash1);
  tcase_add_test(tc, simple_x_wiht_hash2);
  tcase_add_test(tc, simple_x_wiht_hash3);
  tcase_add_test(tc, simple_x_wiht_hash4);
  tcase_add_test(tc, simple_x_wiht_hash5);
  tcase_add_test(tc, simple_x_wiht_hash6);
  tcase_add_test(tc, simple_x_zero_precision_zero_number);
  return s;
}
