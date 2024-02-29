#include "s21_decimal.h"

int s21_is_zero(s21_decimal value) {
  int code = 1;
  for (int row = 0; row < 3; row++) {
    if (value.bits[row] != 0) {
      code = 0;
      break;
    }
  }
  return code;
}

int s21_normalisation(s21_decimal *value1, s21_decimal *value2) {
  int n1 = s21_get_exp(*value1);
  int n2 = s21_get_exp(*value2);
  s21_decimal a = {{0}}, b = {{0}};
  s21_copy(*value1, &a);
  s21_copy(*value2, &b);
  int n3 = n1 > n2 ? n1 : n2;
  int p = 0;
  if (n1 > n2) {
    for (int i = 0; i < n1 - n2; i++) p += s21_mul_by_ten(b, &b);
  } else {
    for (int i = 0; i < n2 - n1; i++) p += s21_mul_by_ten(a, &a);
  }
  if (p != 0) {
    n3 = -1;
  } else {
    s21_copy(a, value1);
    s21_copy(b, value2);
    s21_set_exp(value1, n3);
    s21_set_exp(value2, n3);
  }
  return n3;
}

int s21_get_exp(s21_decimal number) {
  int scale = 1, result = 0;
  for (int i = 112; i < 117; i++) {
    if (s21_get_bit(number, i)) {
      result += scale;
    }
    scale <<= 1;
  }
  return result;
}

void s21_set_exp(s21_decimal *value, int scale) {
  int scale_index = 112;
  if (scale > 28) scale = 28;
  if (s21_is_negative(*value))
    value->bits[3] = 0b10000000000000000000000000000000;
  else
    value->bits[3] = 0;

  while (scale != 0) {
    if ((scale & 0x1) == 0x1) s21_set_bit(value, scale_index, 1);
    scale >>= 1;
    scale_index++;
  }
}

void s21_copy(s21_decimal number, s21_decimal *result) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = number.bits[i];
  }
}

void s21_invert_bit(s21_decimal *number, int index) {
  int ind = s21_get_index(index);
  int i = s21_get_digit(index);
  if (i >= 0 && i <= 3) {
    number->bits[i] ^= 1 << ind;
  }
}

void s21_div_by_ten(s21_decimal value, s21_decimal *result) {
  result->bits[3] = value.bits[3];
  result->bits[2] = (int)(value.bits[2] / 10);
  int x = 10 * (value.bits[2] - result->bits[2]);
  result->bits[1] = (int)((value.bits[1] + x * INT_MAX) / 10);
  x = 10 * (value.bits[1] - result->bits[1]);
  result->bits[0] = (int)((value.bits[0] + x * INT_MAX) / 10);
  x = (int)fmod(value.bits[0], 10);
}

int s21_mul_by_ten(s21_decimal value, s21_decimal *result) {
  int ret = 0;
  int scale = s21_get_exp(value);
  float x = s21_seg(value.bits[0]) + LONG_MAX * s21_seg(value.bits[1]) +
            LONGG_LONG_MAX * s21_seg(value.bits[2]);
  x = x * 10;
  scale = scale - 1;
  if (scale < 0) scale = 0;
  if (fabs(x / pow(10, scale)) > S21_MAX) {
    ret++;
  } else {
    if (x >= LONGG_LONG_MAX) {
      result->bits[2] = s21_dec(trunc(x / LONGG_LONG_MAX));
      result->bits[1] =
          s21_dec(trunc((x - trunc(x / LONGG_LONG_MAX) / LONG_MAX)));
      result->bits[0] =
          s21_dec(x - trunc((x - trunc(x / LONGG_LONG_MAX) / LONG_MAX)));
    } else if (x >= LONG_MAX) {
      result->bits[0] = s21_dec(x - trunc(x / LONG_MAX));
      result->bits[1] = s21_dec(trunc(x / LONG_MAX));
    } else {
      result->bits[0] = s21_dec(x);
    }
    result->bits[3] = 0;
    s21_set_exp(result, scale);
    if (s21_is_negative(value)) s21_negate(*result, result);
  }
  return ret;
}

int s21_get_digit(int index) { return index >> 5; }

int s21_get_index(int index) { return index % 32; }

void s21_set_bit(s21_decimal *number, int index, int bit) {
  int ind = s21_get_index(index);
  int mask = 1 << ind;
  int i = s21_get_digit(index);
  if (number) {
    number->bits[i] &= ~mask;
    if (bit) {
      number->bits[i] |= mask;
    }
  }
}

void s21_empty_decimal(s21_decimal *result) {
  result->bits[3] = 0;
  result->bits[2] = 0;
  result->bits[1] = 0;
  result->bits[0] = 0;
}

void s21_to_big_dec(s21_decimal a, s21_big_decimal *b) {
  for (int i = 0; i < 3; i++) {
    b->bits[i] = a.bits[i];
  }
  for (int i = 3; i < 8; i++) {
    b->bits[i] = 0;
  }
  b->n = s21_get_exp(a);
  if (s21_is_negative(a)) b->n *= -1;
}

int s21_from_big(s21_big_decimal a, s21_decimal *b) {
  int output = 0;
  int sign = 0;
  int scale = a.n;
  if (a.n < 0) {
    scale = a.n * -1;
    sign += 1;
  }
  s21_empty_decimal(b);
  if (scale <= 28 && a.bits[3] == 0 && a.bits[4] == 0 && a.bits[5] == 0 &&
      a.bits[6] == 0 && a.bits[7] == 0) {
    for (int i = 0; i < 3; i++) {
      b->bits[i] = a.bits[i];
    }
    b->bits[3] = 0;
    s21_set_exp(b, scale);
    if (sign) s21_negate(*b, b);
    for (int i = 0; i < 3; i++) /*if (b->bits[i] < 0)*/
      b->bits[i] = -1;
  } else {
    output = 1;
  }
  return output;
}

int s21_is_negative(s21_decimal number) { return s21_get_bit(number, 127); }

// int s21_negate(s21_decimal value, s21_decimal *result) {
//   s21_empty_decimal(result);
//   s21_copy(value, result);
//   s21_invert_bit(result, 127);
//   return 0;
// }

void s21_optimise(s21_decimal *val) {
  int n = s21_get_exp(*val);
  if (n != 0 && val->bits[0] % 10 == 0) {
    while (n) {
      if (val->bits[0] % 10 == 0) {
        s21_div_by_ten(*val, val);
        n--;
      } else {
        break;
      }
    }
  }
  s21_set_exp(val, n);
}

int s21_get_bit(s21_decimal number, int index) {
  int i = s21_get_digit(index);
  int ind = s21_get_index(index);
  return (number.bits[i] >> ind) & 1;
}

int add_for_mul(s21_big_decimal res_value, s21_big_decimal value_1,
                s21_big_decimal *res) {
  int check = 0;
  int add_bit = 0;
  for (int i = 0; i < 192; i++) {
    int a = get_bit(value_1.bits[i / 32], i % 32);
    int b = get_bit(res_value.bits[i / 32], i % 32);
    set_bit(&(res->bits[i / 32]), i % 32, a ^ b ^ add_bit);
    add_bit = (a && b) || (b && add_bit) || (a && add_bit);
  }
  if (add_bit) check = 1;
  return check;
}

void left_shift_big(s21_big_decimal *value) {
  int old = 0;
  for (int i = 0; i < 6; i++) {
    int new_bit = get_bit(value->bits[i], 31);
    value->bits[i] = value->bits[i] << 1;
    set_bit(&(value->bits[i]), 0, old);
    old = new_bit;
  }
}

void right_shift(s21_big_decimal *value) {
  int old = 0;
  for (int i = 7; i >= 0; i--) {
    int new_bit = get_bit(value->bits[i], 0);
    value->bits[i] = value->bits[i] >> 1;
    set_bit(&(value->bits[i]), 31, old);
    old = new_bit;
  }
}

void s21_big_div_by_ten(s21_big_decimal *src) {
  unsigned long long last, div;

  div = 0;
  for (int i = 5; i >= 0; i--) {
    last = (unsigned int)(src->bits[i]) + div * 2 * D;
    div = last % 10;
    src->bits[i] = (int)((unsigned int)(last / 10));
  }
  --src->n;
}

int get_bit(int src, int pos) {
  if (src & (1 << pos)) {
    return 1;
  } else {
    return 0;
  }
}

void set_bit(int *dst, int pos, int value) {
  if (value) {
    *dst |= (1 << pos);
  } else {
    *dst &= ~(1 << pos);
  }
}

long int s21_seg(int a) {
  long int ret = a;
  if (a < 0) ret = a + 2 * D;
  return ret;
}

int s21_dec(float a) {
  if (a >= D) a = -2 * D + a;
  return (int)a;
}

void s21_big_mult(s21_big_decimal a, s21_big_decimal b, s21_big_decimal *res) {
  int check = 0;
  int flag = 0;
  if (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0 && b.bits[3] == 0 &&
      b.bits[4] == 0 && b.bits[5] == 0 && b.bits[6] == 0 && b.bits[7] == 0)
    flag = 1;
  while (!flag && !check) {
    if (get_bit(b.bits[0], 0)) {
      check = add_for_mul(*res, a, res);
    }
    left_shift_big(&a);
    if (get_bit(res->bits[5], 31)) {
      check = 1;
    }
    right_shift(&b);
    if (b.bits[0] == 0 && b.bits[1] == 0 && b.bits[2] == 0 && b.bits[3] == 0 &&
        b.bits[4] == 0 && b.bits[5] == 0 && b.bits[6] == 0 && b.bits[7] == 0)
      flag = 1;
  }
  res->n = a.n + b.n;
  while (((res->bits[5] || res->bits[4] || res->bits[3]) && res->n != 0) ||
         res->n > 28) {
    s21_big_div_by_ten(res);
  }
}

void s21_truncate_modules(s21_decimal_long *value, int scale) {
  s21_decimal_long value_const = {0}, temp = {0};
  value_const.bits[0] = 10;
  memcpy(temp.bits, value->bits, sizeof(value->bits));

  for (int i = 0; i < scale; i++) {
    memset(value->bits, 0, sizeof(value->bits));
    s21_div_modules(temp, value_const, value);
    memcpy(temp.bits, value->bits, sizeof(value->bits));
  }
}

void s21_parse_mul(s21_decimal_long tmp_val_1, s21_decimal_long tmp_val_2,
                   s21_decimal_long *tmp_res, s21_decimal value_1,
                   s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int scale_1 = s21_get_the_scale(value_1);
  int scale_2 = s21_get_the_scale(value_2);

  if (scale_1 >= scale_2) {
    s21_set_the_scale(result, (scale_1 + scale_2));
  } else {
    s21_set_the_scale(result, (scale_2 + scale_1));
  }

  if (sign_1 != sign_2) s21_set_bit_true(result, 127);
  s21_mul_modules(tmp_val_1, tmp_val_2, tmp_res);
}

int s21_round_result(s21_decimal *result, s21_decimal_long value) {
  s21_decimal_long temp_int = {0};
  int sign = s21_get_sign(*result);
  int bit_depth = s21_bits_len(value), output = 0;
  int scale = s21_get_the_scale(*result);
  memcpy(temp_int.bits, value.bits, sizeof(value.bits));
  s21_truncate_modules(&temp_int, scale);
  int bit_depth_truncate = s21_bits_len(temp_int);

  if (bit_depth && (bit_depth_truncate <= 96)) {
    s21_truncate_nulls(&value, result);
    if (s21_get_the_scale(*result) == 1) {
      bit_depth = s21_rounding(&value, result, 96, 2);
    } else {
      bit_depth = s21_rounding(&value, result, 96, 0);
    }
  }
  if (sign) s21_set_bit_true(result, 127);
  if (bit_depth > 96 || bit_depth_truncate > 96) {
    memset(value.bits, 0, sizeof(value.bits));
    output = s21_get_sign(*result) ? 2 : 1;
  }
  memcpy(result->bits, value.bits, (sizeof(uint) * 3));

  return output;
}

int s21_is_equal_modules(s21_decimal_long value_1, s21_decimal_long value_2) {
  return value_1.bits[6] == value_2.bits[6] &&
         value_1.bits[5] == value_2.bits[5] &&
         value_1.bits[4] == value_2.bits[4] &&
         value_1.bits[3] == value_2.bits[3] &&
         value_1.bits[2] == value_2.bits[2] &&
         value_1.bits[1] == value_2.bits[1] &&
         value_1.bits[0] == value_2.bits[0];
}

void s21_normalize_add_modules(s21_decimal_long *value_1,
                               s21_decimal_long *value_2, s21_decimal *result,
                               int scale_1, int scale_2) {
  if (scale_1 >= scale_2) {
    s21_set_the_scale(result, scale_1);
    s21_normalize(value_2, (scale_1 - scale_2));
  } else {
    s21_set_the_scale(result, scale_2);
    s21_normalize(value_1, (scale_2 - scale_1));
  }
}

int s21_is_greater_modules(s21_decimal_long value_1, s21_decimal_long value_2) {
  int res = 0;

  for (int i = 6; i >= 0; i--) {
    if (value_1.bits[i] > value_2.bits[i]) {
      res = 1;
      break;
    } else if (value_1.bits[i] < value_2.bits[i]) {
      break;
    }
  }

  return res;
}

int s21_is_less_modules(s21_decimal_long value_1, s21_decimal_long value_2) {
  return (!(s21_is_greater_modules(value_1, value_2) ||
            s21_is_equal_modules(value_1, value_2)));
}

void s21_set_the_scale(s21_decimal *value, int scale) {
  value->bits[3] = ((value->bits[3] + scale) << 16);
}

void s21_set_bit_true(s21_decimal *value, int pos) {
  value->bits[pos / 32] |= (1 << (pos % 32));
}

void s21_parse_dec(float tmp_src, float src, s21_decimal *dst) {
  int exp = s21_get_exponent(tmp_src);
  tmp_src /= powf(10, (float)exp);
  dst->bits[0] = (int)tmp_src;
  if ((dst->bits[0] % 10) >= 5) {
    dst->bits[0] = (dst->bits[0] / 10) + 1;
  } else {
    dst->bits[0] /= 10;
  }
  s21_decimal tmp = {{10, 0, 0, 0}};
  for (int i = 0; i < (exp + 1); i++) s21_mul(*dst, tmp, dst);
  if (src < 0) s21_set_bit_true(dst, 127);
}

int s21_bits_len(s21_decimal_long value) {
  int res = 0;
  s21_decimal_long null = {0};
  s21_decimal_long temp_value;
  memcpy(temp_value.bits, value.bits, sizeof(value.bits));

  while (!s21_is_equal_modules(temp_value, null)) {
    s21_rshift(&temp_value);
    res++;
  }

  return res;
}

int s21_rounding_fractions(s21_decimal *value, int bits, int method) {
  s21_decimal_long tmp_value = {0};
  int sign = s21_get_sign(*value);
  memcpy(tmp_value.bits, value->bits, (sizeof(uint) * 3));

  switch (method) {
    case -1:
      s21_truncate_nulls(&tmp_value, value);
      if (sign) s21_set_bit_true(value, 127);
      s21_rounding(&tmp_value, value, bits, method);
      break;
    case 0:
      s21_rounding(&tmp_value, value, bits, method);
      break;
    case 1:
      s21_truncate_nulls(&tmp_value, value);
      s21_rounding(&tmp_value, value, bits, method);
      break;
  }

  memcpy(value->bits, tmp_value.bits, (sizeof(uint) * 3));
  if (sign) s21_set_bit_true(value, 127);

  return s21_bits_len(tmp_value);
}

int s21_parse_float(s21_decimal *tmp_src, float *dst, int sign) {
  int exp = 0;
  s21_decimal_long temp = {0};
  memcpy(temp.bits, tmp_src->bits, (sizeof(uint) * 3));
  while (temp.bits[0]) {
    s21_truncate_modules(&temp, 1);
    exp++;
  }
  exp = exp - 8;
  memcpy(temp.bits, tmp_src->bits, (sizeof(uint) * 3));
  s21_truncate_modules(&temp, exp);
  if ((temp.bits[0] % 10) >= 5) {
    temp.bits[0] = (temp.bits[0] / 10) + 1;
  } else {
    temp.bits[0] /= 10;
  }
  *dst = temp.bits[0];
  *dst *= powf(10, (float)(exp + 1));
  if (sign) *dst *= -1;

  return (exp + 1) ? 0 : 1;
}

int s21_parse_rounding(s21_decimal *value, int method) {
  int output = 0;
  s21_decimal_long tmp_value = {0};
  memcpy(tmp_value.bits, value->bits, (sizeof(uint) * 3));
  int bit_depth = s21_bits_len(tmp_value);
  int scale = s21_get_the_scale(*value);

  if (bit_depth && scale <= 28 && scale >= 0) {
    s21_truncate_modules(&tmp_value, scale);
    bit_depth = s21_bits_len(tmp_value);
    output = s21_rounding_fractions(value, bit_depth, method);
  } else {
    int sign = s21_get_sign(*value);
    s21_set_the_scale(value, 0);
    if (sign) s21_set_bit_true(value, 127);
  }

  return output > 96 ? 1 : 0;
}

void s21_set_bit_false(s21_decimal *value, int pos) {
  value->bits[pos / 32] &= (~(1 << (pos % 32)));
}

int s21_get_sign(s21_decimal value) { return (value.bits[3] & 2147483648); }

void s21_div_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result) {
  s21_decimal_long temp_1, temp_2;  // вариант_2
  memcpy(temp_1.bits, value_1.bits, sizeof(value_1));
  while (s21_is_greater_or_equal_modules(temp_1, value_2)) {
    int i = 0;
    memcpy(temp_2.bits, value_2.bits, sizeof(value_2));
    while (s21_is_greater_or_equal_modules(temp_1, s21_lshift_out(temp_2))) {
      i++;
      s21_lshift(&temp_2);
    }
    s21_set_n_bit_true(result, i);
    s21_sub_modules(temp_1, temp_2, &temp_1);
  }
}

void s21_mul_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result) {
  s21_decimal_long temp_1, temp_2;
  memcpy(temp_1.bits, value_1.bits, sizeof(value_1));
  memcpy(temp_2.bits, value_2.bits, sizeof(value_2));
  for (int t = 0; t < (7 * 32); t++) {
    if (temp_2.bits[0] & 1) {
      s21_add_modules(*result, temp_1, result);
    }
    s21_lshift(&temp_1);
    s21_rshift(&temp_2);
  }
}

int s21_get_the_scale(s21_decimal value) {
  return ((value.bits[3] << 8) >> 24);
}

void s21_truncate_nulls(s21_decimal_long *value, s21_decimal *result) {
  s21_decimal_long temp = {0}, ten = {0};
  ten.bits[0] = 10;
  int result_int = s21_get_the_scale(*result);
  s21_mod_modules(*value, ten, &temp);
  while (!temp.bits[0] && result_int) {
    result_int--;
    s21_truncate_modules(value, 1);
    memset(temp.bits, 0, sizeof(temp.bits));
    s21_mod_modules(*value, ten, &temp);
  }
  s21_set_the_scale(result, result_int);
}

s21_decimal_long s21_lshift_out(s21_decimal_long value) {
  s21_decimal_long tmp;
  memcpy(tmp.bits, value.bits, sizeof(value));
  s21_lshift(&tmp);
  return tmp;
}

void s21_set_n_bit_true(s21_decimal_long *value, int pos) {
  value->bits[pos / 32] |= (1 << (pos % 32));
}

void s21_add_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result) {
  int64_t temp = 0, carry = 0;  // Временная переменная и разряд переноса
  s21_decimal_long tmp;
  memcpy(tmp.bits, value_1.bits, sizeof(value_1));
  for (int i = 0; i < 7; i++) {
    result->bits[i] = temp = (int64_t)tmp.bits[i] + value_2.bits[i] + carry;
    carry = temp >> 32;  // Оставляем только перенос в следующий разряд
  }
}

void s21_mod_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result) {
  s21_decimal_long res = {0};
  s21_div_modules(value_1, value_2, &res);
  s21_mul_modules(res, value_2, result);
  s21_sub_modules(value_1, *result, result);
}

void s21_sub_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result) {
  s21_decimal_long temp;
  memcpy(temp.bits, value_2.bits, sizeof(value_2));
  s21_neg(&temp);
  s21_add_modules(value_1, temp, result);
}

int s21_rounding(s21_decimal_long *value, s21_decimal *result, int bits,
                 int method) {
  int bit_depth = s21_bits_len(*value);
  int sign = s21_get_sign(*result);
  int scale = s21_get_the_scale(*result);
  s21_decimal_long const_ten = {0}, const_one = {0};
  const_one.bits[0] = 1, const_ten.bits[0] = 10;
  s21_decimal_long temp_fractions = {0};
  memcpy(temp_fractions.bits, value->bits, sizeof(value->bits));

  while ((bit_depth > bits && scale) || scale > 28) {
    scale--;
    s21_decimal_long temp_res = {0};
    s21_mod_modules(temp_fractions, const_ten, &temp_res);
    s21_truncate_modules(value, 1);
    s21_truncate_modules(&temp_fractions, 1);
    bit_depth = s21_bits_len(*value);

    if (temp_res.bits[0] >= 5 && method == 0) {
      if (bit_depth <= bits && scale <= 28)
        s21_add_modules(*value, const_one, value);
    } else if (temp_res.bits[0] && method == -1) {
      if (sign && bit_depth <= bits && !scale)
        s21_add_modules(*value, const_one, value);
    } else if (temp_res.bits[0] >= 5 && method == 1) {
      if (bit_depth <= bits && !scale)
        s21_add_modules(*value, const_one, value);
    }
    if (temp_res.bits[0] >= 5 &&
        (!scale || (bit_depth <= bits && scale <= 28)) && method == 2) {
      temp_res.bits[0] = 0;
      s21_mod_modules(*value, const_ten, &temp_res);
      if (temp_res.bits[0] % 2) s21_add_modules(*value, const_one, value);
    }
    temp_res.bits[0] = 0;
    bit_depth = s21_bits_len(*value);
  }
  s21_set_the_scale(result, scale);

  return bit_depth;
}

void s21_normalize(s21_decimal_long *value, int scale_diff) {
  s21_decimal_long value_const = {0};
  value_const.bits[0] = 9;

  for (int i = 0; i < scale_diff; i++)
    s21_mul_modules(*value, value_const, value);
}

int s21_get_exponent(float value) {
  int exp = 0;
  while (value >= 1) {
    value /= 10;
    exp++;
  }
  return (exp - 8);
}

void s21_rshift(s21_decimal_long *value) {
  int64_t carry = 0, temp = 0;
  carry = (((int64_t)value->bits[6] & (1 << 31)) != 0);
  for (int i = 6; i >= 0; i--) {
    temp = (int64_t)value->bits[i] & 1;  // Выделить младший разряд (перенос)
    value->bits[i] >>= 1;  // Сдвинуть вправо и установить
    value->bits[i] |= carry << 31;  // старый перенос в старший разряд
    carry = temp;  // Запомнить новый перенос
  }
}

int s21_is_greater_or_equal_modules(s21_decimal_long value_1,
                                    s21_decimal_long value_2) {
  return (s21_is_equal_modules(value_1, value_2) ||
          s21_is_greater_modules(value_1, value_2));
}

void s21_lshift(s21_decimal_long *value) {
  int64_t carry = 0, temp = 0;
  for (int i = 0; i < 7; i++) {
    temp = ((int64_t)value->bits[i] & (1 << 31)) >>
           31;  // Выделить старший разряд (перенос)
    value->bits[i] <<= 1;  // Сдвинуть влево и установить
    value->bits[i] |= carry;  // старый перенос в младший разряд
    carry = temp;             // Запомнить новый перенос
  }
}

void s21_neg(s21_decimal_long *value) {
  int64_t temp = 0, carry = 1;
  for (int i = 0; i < 7; i++)
    value->bits[i] = ~value->bits[i];  // Инвертирование всех разрядов
  for (int t = 0; t < 7; t++) {
    value->bits[t] = temp = (int64_t)value->bits[t] + carry;
    carry = (temp & 4294967296) >> 32;
  }
}
