#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_setZero(dst);
  int return_result = (src > INT_MAX) ? 1 : 0;
  dst->bits[0] = (src < 0) ? ((dst->bits[3] = 1 << 31, -src)) : src;
  return return_result;
}
