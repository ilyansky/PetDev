#include "s21_decimal.h"

int s21_is_equal(s21_decimal a, s21_decimal b) {
  int code = 1;
  if ((s21_is_zero(a) ^ s21_is_zero(b))) {
    code = 0;
  } else if ((s21_is_zero(a) && s21_is_zero(b))) {
    code = 1;
  } else {
    s21_optimise(&a);
    s21_optimise(&b);
    for (int i = 0; i < 4; i++)
      if (a.bits[i] != b.bits[i]) {
        code = 0;
        break;
      }
  }
  return code;
}
