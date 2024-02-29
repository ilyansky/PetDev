#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int output = 1;
  if (result != NULL) {
    memcpy(result->bits, value.bits, sizeof(value.bits));
    output = s21_parse_rounding(result, 1);
  }

  return output;
}
