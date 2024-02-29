#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal plug = {0};
  s21_decimal_long const_null = {0};
  s21_decimal_long tmp_val_1 = {0}, tmp_val_2 = {0};
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int scale_1 = s21_get_the_scale(value_1);
  int scale_2 = s21_get_the_scale(value_2);

  memcpy(tmp_val_1.bits, value_1.bits, (sizeof(uint) * 3));
  memcpy(tmp_val_2.bits, value_2.bits, (sizeof(uint) * 3));

  if (!(s21_is_equal_modules(tmp_val_1, const_null) &&
        s21_is_equal_modules(tmp_val_2, const_null))) {
    s21_normalize_add_modules(&tmp_val_1, &tmp_val_2, &plug, scale_1, scale_2);
    if (sign_1 && sign_2) {
      result = s21_is_greater_modules(tmp_val_1, tmp_val_2);
    } else if (!sign_1 && !sign_2) {
      result = s21_is_less_modules(tmp_val_1, tmp_val_2);
    } else if (sign_1 && !sign_2) {
      result = 1;
    }
  }

  return result;
}
