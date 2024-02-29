#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int output = 0;
  s21_decimal_long tmp_val_1 = {0}, tmp_val_2 = {0}, tmp_res = {0};

  if (result != NULL) {
    memset(result->bits, 0, sizeof(result->bits));
    memcpy(tmp_val_1.bits, value_1.bits, (sizeof(uint) * 3));
    memcpy(tmp_val_2.bits, value_2.bits, (sizeof(uint) * 3));
    s21_parse_mul(tmp_val_1, tmp_val_2, &tmp_res, value_1, value_2, result);
    output = s21_round_result(result, tmp_res);
  }

  return output;
}
