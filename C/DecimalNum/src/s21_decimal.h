#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
// Случай, когда у числа все единицы

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OneAt31 1 << 31
#define ZeroBits 0b00000000000000000000000000000000
#define MinusZeroBits 0b10000000000000000000000000000000
#define OneAt0 0b00000000000000000000000000000001
#define TenBits 0b00000000000000000000000000001010
#define OverloadBits 0b11111000000000000000000000000000
#define Bits3 0b00000000000000000000000011111111
#define MaxInt 0b11111111111111111111111111111111
#define MaxIntMinusOne 0b11111111111111111111111111111110

#define ZeroAt31 0b01111111111111111111111111111111
#define FindScale(bits) ((bits >> 16) & Bits3)

#define min 1e-28
#define D 2147483648.0
#define inf 1.0 / 0.0
#define maxix -1
#define S21_MAX 79228162514264337593543950335.0
#define LONGG_LONG_MAX 18446744073709552000.0  // CHECKME
#define S21_INFINITY 1.0 / 0.0
#define MAX 79228162514264337593543950335.0F
#define MIN -79228162514264337593543950335.0F

typedef unsigned int uint;

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  int bits[8];
  int n;
} s21_big_decimal;

typedef struct {
  uint bits[7];
} s21_decimal_long;

// CHECKME: где ставить запятую при оверлоаде?
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
// Инициализирует число децимал
void s21_initDecimal(int num3, int num2, int num1, int num0, s21_decimal *num);
// Складывает 2 инта
void s21_sumTwoInts(int num1, int num2, int *inMind, s21_decimal *result,
                    int ind);
// Вычитает из одного инта второй
void s21_subTwoInts(int num1, int num2, int *inMind, s21_decimal *result,
                    int ind);
// Умножает число на 2
int s21_mulNumBy2(s21_decimal *num);
// Умножает число на 10
int s21_mulNumBy10(s21_decimal *num);
// Приводит к общему знаменателю | ADDME: пока что только умножает на 10, в
// теории должно еще и делить
int s21_leadToCommonDenominator(s21_decimal *num, int amount);
// Выводит число децимал в битах
void s21_printDecimalNum(s21_decimal num);
// Считает количество значащих битов в числе
int s21_countBits(s21_decimal num);  // Потестить
int s21_findGreatestVal(s21_decimal val1, s21_decimal val2);

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//----------

int s21_is_zero(s21_decimal value);
int s21_normalisation(s21_decimal *value1, s21_decimal *value2);

int s21_get_exp(s21_decimal number);
void s21_set_exp(s21_decimal *value, int scale);
void s21_copy(s21_decimal number, s21_decimal *result);
void s21_invert_bit(s21_decimal *number, int index);
void s21_div_by_ten(s21_decimal value, s21_decimal *result);
int s21_mul_by_ten(s21_decimal value, s21_decimal *result);
int s21_get_digit(int index);
int s21_get_index(int index);
void s21_set_bit(s21_decimal *number, int index, int bit);

void s21_empty_decimal(s21_decimal *result);
void s21_to_big_dec(s21_decimal a, s21_big_decimal *b);
int s21_from_big(s21_big_decimal a, s21_decimal *b);
int s21_is_negative(s21_decimal number);

void s21_optimise(s21_decimal *val);
int s21_get_bit(s21_decimal number, int index);
int add_for_mul(s21_big_decimal res_value, s21_big_decimal value_1,
                s21_big_decimal *res);
void left_shift_big(s21_big_decimal *value);
void right_shift(s21_big_decimal *value);
void s21_big_div_by_ten(s21_big_decimal *src);
int get_bit(int src, int pos);
void set_bit(int *dst, int pos, int value);
long int s21_seg(int a);
int s21_dec(float a);
void s21_big_mult(s21_big_decimal a, s21_big_decimal b,
                  s21_big_decimal *result);

//
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
//

int check_number(float src, int exp);
void s21_setZero(s21_decimal *numDec);
unsigned int s21_GetSign(float src);
void parse_float(float num, float *new_num, int *scale);

//
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
//
int s21_is_zero(s21_decimal value);
int s21_normalisation(s21_decimal *value1, s21_decimal *value2);

int s21_get_exp(s21_decimal number);
void s21_set_exp(s21_decimal *value, int scale);
void s21_copy(s21_decimal number, s21_decimal *result);
void s21_invert_bit(s21_decimal *number, int index);
void s21_div_by_ten(s21_decimal value, s21_decimal *result);
int s21_mul_by_ten(s21_decimal value, s21_decimal *result);
int s21_get_digit(int index);
int s21_get_index(int index);
void s21_set_bit(s21_decimal *number, int index, int bit);

void s21_empty_decimal(s21_decimal *result);
void s21_to_big_dec(s21_decimal a, s21_big_decimal *b);
int s21_from_big(s21_big_decimal a, s21_decimal *b);
int s21_is_negative(s21_decimal number);
void s21_optimise(s21_decimal *val);
int s21_get_bit(s21_decimal number, int index);
int add_for_mul(s21_big_decimal res_value, s21_big_decimal value_1,
                s21_big_decimal *res);
void left_shift_big(s21_big_decimal *value);
void right_shift(s21_big_decimal *value);
void s21_big_div_by_ten(s21_big_decimal *src);
int get_bit(int src, int pos);
void set_bit(int *dst, int pos, int value);
long int s21_seg(int a);
int s21_dec(float a);
void s21_big_mult(s21_big_decimal a, s21_big_decimal b,
                  s21_big_decimal *result);

void s21_truncate_modules(s21_decimal_long *value, int scale);
void s21_parse_mul(s21_decimal_long tmp_val_1, s21_decimal_long tmp_val_2,
                   s21_decimal_long *tmp_res, s21_decimal value_1,
                   s21_decimal value_2, s21_decimal *result);
int s21_round_result(s21_decimal *result, s21_decimal_long value);
int s21_is_equal_modules(s21_decimal_long value_1, s21_decimal_long value_2);
void s21_normalize_add_modules(s21_decimal_long *value_1,
                               s21_decimal_long *value_2, s21_decimal *result,
                               int scale_1, int scale_2);
int s21_is_greater_modules(s21_decimal_long value_1, s21_decimal_long value_2);
int s21_is_less_modules(s21_decimal_long value_1, s21_decimal_long value_2);
void s21_set_the_scale(s21_decimal *value, int scale);
void s21_set_bit_true(s21_decimal *value, int pos);
void s21_parse_dec(float tmp_src, float src, s21_decimal *dst);
int s21_bits_len(s21_decimal_long value);
int s21_rounding_fractions(s21_decimal *value, int bits, int method);
int s21_parse_float(s21_decimal *tmp_src, float *dst, int sign);
int s21_parse_rounding(s21_decimal *value, int method);
void s21_set_bit_false(s21_decimal *value, int pos);
int s21_get_sign(s21_decimal value);
void s21_div_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result);
void s21_mul_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result);
int s21_get_the_scale(s21_decimal value);
void s21_truncate_nulls(s21_decimal_long *value, s21_decimal *result);
s21_decimal_long s21_lshift_out(s21_decimal_long value);
void s21_set_n_bit_true(s21_decimal_long *value, int pos);
void s21_add_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result);
void s21_mod_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result);
void s21_sub_modules(s21_decimal_long value_1, s21_decimal_long value_2,
                     s21_decimal_long *result);
int s21_rounding(s21_decimal_long *value, s21_decimal *result, int bits,
                 int method);
void s21_normalize(s21_decimal_long *value, int scale_diff);
int s21_get_exponent(float value);
void s21_rshift(s21_decimal_long *value);
int s21_is_greater_or_equal_modules(s21_decimal_long value_1,
                                    s21_decimal_long value_2);
void s21_lshift(s21_decimal_long *value);
void s21_neg(s21_decimal_long *value);

//
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
//

//
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
//

int check_number(float src, int exp);
void s21_setZero(s21_decimal *numDec);
unsigned int s21_GetSign(float src);
void parse_float(float num, float *new_num, int *scale);

//
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
//

#endif
