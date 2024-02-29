#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int output = 1;
  int scale = 0;
  int bit_depth = 0;

  memset(dst->bits, 0, sizeof(dst->bits));
  if (!isinf(src) && !isinf(-src) && (src <= MAX && src >= MIN) &&
      dst != NULL) {
    float tmp_src = src;

    if (tmp_src < 0) tmp_src /= -1;
    while (tmp_src > (int)tmp_src) {
      tmp_src *= 10;
      scale += 1;
    }
    int tmp_int = (int)tmp_src;
    for (; tmp_int; bit_depth++) tmp_int >>= 1;
    while (bit_depth > 23 && scale) {
      scale -= 1;
      bit_depth = 0;
      int temp = (int)tmp_src;
      int mod = temp % 10;
      tmp_src = tmp_src / 10;
      tmp_int = tmp_src;
      for (; tmp_int; bit_depth++) tmp_int >>= 1;
      if (mod >= 5 && bit_depth <= 23) tmp_src += 1;
    }
    if (bit_depth <= 23) {
      dst->bits[0] = (int)tmp_src;
      s21_set_the_scale(dst, scale);
      if (src < 0) s21_set_bit_true(dst, 127);
    } else {
      s21_parse_dec(tmp_src, src, dst);
    }
    output = 0;
  }

  return output;
}
