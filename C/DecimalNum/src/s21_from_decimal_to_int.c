#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int output = 1;
  s21_decimal_long tmp_src = {0};
  int sign = s21_get_sign(src);
  int scale = s21_get_the_scale(src);

  if (dst != NULL) {
    memcpy(tmp_src.bits, src.bits, (sizeof(uint) * 3));
    s21_truncate_modules(&tmp_src, scale);
    int len = s21_bits_len(tmp_src);
    if (len <= 32 && (tmp_src.bits[0] <= (uint)INT_MAX ||
                      (tmp_src.bits[0] == (uint)INT_MIN && sign))) {
      *dst = tmp_src.bits[0];
      if (sign) *dst = (~*dst) + 1;
      output = 0;
    } else {
      *dst = 0;
    }
  }

  return output;
}
