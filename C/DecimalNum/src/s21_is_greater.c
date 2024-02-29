#include "s21_decimal.h"

int s21_is_greater(s21_decimal a, s21_decimal b) {
  int code = -1;
  if (s21_is_negative(a) && !s21_is_negative(b)) code = 0;
  if (!s21_is_negative(a) && s21_is_negative(b)) code = 1;
  if (s21_is_equal(a, b)) code = 0;
  if (code == -1) {
    s21_optimise(&a);
    s21_optimise(&b);
    s21_normalisation(&a, &b);
    code = 1;
    for (int i = 95; i > -1; i--) {
      if (s21_get_bit(a, i) < s21_get_bit(b, i)) {
        code = 0;
        break;
      }
      if (s21_get_bit(a, i) > s21_get_bit(b, i)) {
        break;
      }
    }
    if (s21_is_negative(a) && s21_is_negative(b)) code = !code;
  }
  return code;
}
