#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  result->bits[3] = value_1.bits[3];
  result->bits[2] = value_2.bits[2];
  return 1;
}
