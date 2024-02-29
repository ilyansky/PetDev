#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int output = 1;

  if (dst != NULL) {
    *dst = 0;
    s21_decimal tmp_src = {0};
    memcpy(tmp_src.bits, src.bits, sizeof(src.bits));
    int sign = s21_get_sign(src);
    if (s21_rounding_fractions(&tmp_src, 23, 0) <= 23) {
      int scale = s21_get_the_scale(tmp_src);
      float fractions = powf(10, (float)scale);
      *dst = tmp_src.bits[0];
      if (sign) *dst *= -1;
      *dst /= fractions;
      output = 0;
    } else {
      output = s21_parse_float(&tmp_src, dst, sign);
    }
  }

  return output;
}
