#include <check.h>

#include "../s21_decimal.h"

#define MAX_INT 2147483647   // 0b01111111111111111111111111111111
#define MAX_UINT 4294967295  // 0b11111111111111111111111111111111
#define MINUS 2147483648     // 0b10000000000000000000000000000000
#define EXPONENT_20 1310720  // 0b00000000000101000000000000000000

/// =============== VARIABLES ===============
s21_decimal max = {{MAX_UINT, MAX_UINT, MAX_UINT, 0}};
s21_decimal middle = {{MAX_INT, MAX_INT, MAX_INT, 0}};
s21_decimal null = {{0, 0, 0, 0}};
s21_decimal null_minus = {{0, 0, 0, MINUS}};
s21_decimal middle_minus = {{MAX_INT, MAX_INT, MAX_INT, MINUS}};
s21_decimal max_minus = {{MAX_UINT, MAX_UINT, MAX_UINT, MINUS}};
s21_decimal middle_fractions = {{MAX_INT, MAX_INT, MAX_INT, EXPONENT_20}};
s21_decimal middle_fractions_minus = {
    {MAX_INT, MAX_INT, MAX_INT, (EXPONENT_20 | MINUS)}};
s21_decimal round_num = {{4560000, 0, 0, 327680}};
s21_decimal floor_num = {{0, 0, 0, MAX_INT}};
s21_decimal tmp = {{15, 0, 0, MINUS}};
s21_decimal tmp_2 = {{4, 0, 0, 0}};
s21_decimal tmp_float = {{214748413, 0, 0, 0b00000000000000010000000000000000}};

/// ===============   RESULTS  ===============
s21_decimal res_middle_add_middle_fractions = {
    {2543624459, 2147483647, 2147483647, 0}};
s21_decimal res_middle_add_middle = {{4294967294, 4294967294, 4294967294, 0}};
s21_decimal res_middle_minus_add_middle_minus = {
    {4294967294, 4294967294, 4294967294, MINUS}};
s21_decimal res_middle_fractions_add_middle_fractions = {
    {4294967294, 4294967294, 4294967294, EXPONENT_20}};
s21_decimal res_middle_add_max_minus = {
    {2147483648, 2147483648, 2147483648, MINUS}};
s21_decimal res_max_sub_middle = {{2147483648, 2147483648, 2147483648, 0}};
s21_decimal res_middle_fraction_sub_middle_fraction = {
    {20482339, 3303706602, 142724, 0}};
s21_decimal res_middle_fraction_mul_middle_fraction = {
    {3034176889, 3892122324, 850705916, 720896}};
s21_decimal res_middle_fraction_mul_middle_fraction_minus = {
    {3034176889, 3892122324, 850705916, (720896 | MINUS)}};
s21_decimal res_max_div_middle = {{495533628, 3169427839, 1084202172, 1835008}};
s21_decimal res_middle_div_max = {{1489344416, 250255873, 271050543, 1835008}};
s21_decimal res_max_minus_div_middle = {
    {495533628, 3169427839, 1084202172, (1835008 | MINUS)}};
s21_decimal res_max_mod_middle = {{1, 1, 1, 0}};
s21_decimal res_tmp_mod_tmp_2 = {{3, 0, 0, MINUS}};
// =========== CONVERSION & OTHER FUNCTIONS ============
s21_decimal res_floor_middle_fractions = {{396140812, 0, 0, 0}};
s21_decimal res_floor_middle_fractions_minus = {{396140813, 0, 0, MINUS}};
s21_decimal res_round_middle_fractions_minus = {{396140812, 0, 0, MINUS}};
s21_decimal res_round = {{46, 0, 0, 0}};
s21_decimal res_floor = {{0, 0, 0, MINUS}};
s21_decimal res_from_float_to_decimal = {{21474840, 0, 0, 0}};

s21_decimal temp_res = {{0, 0, 0, 0}};

// ADD
s21_decimal test1 = {{MaxInt, MaxInt, MaxInt, ZeroBits}};
s21_decimal res1 = {{MaxIntMinusOne, MaxInt, MaxInt, ZeroBits}};

s21_decimal test21 = {{MaxInt, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal test22 = {{OneAt0, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal res2 = {{ZeroBits, OneAt0, ZeroBits, ZeroBits}};

s21_decimal test31 = {
    {0b00000000000000000000010010110010, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal test32 = {
    {0b00000000000000000000101001111101, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal res3 = {
    {0b00000000000000000000111100101111, ZeroBits, ZeroBits, ZeroBits}};

s21_decimal test41 = {
    {0b00000000000000000000010010110010, ZeroBits, ZeroBits, OneAt31}};
s21_decimal test42 = {
    {0b00000000000000000000101001111101, ZeroBits, ZeroBits, OneAt31}};
s21_decimal res4 = {
    {0b00000000000000000000111100101111, ZeroBits, ZeroBits, OneAt31}};

s21_decimal test51 = {{0b01001111010111110111101100100111,
                       0b00000000000000000000000010010110, ZeroBits, ZeroBits}};
s21_decimal test52 = {
    {0b00000000000000000000101001111101, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal res5 = {{0b01001111010111111000010110100100,
                     0b00000000000000000000000010010110, ZeroBits, ZeroBits}};

s21_decimal test61 = {{MaxInt, MaxInt, MaxInt, OneAt31}};
s21_decimal test62 = {{MaxInt, MaxInt, MaxInt, OneAt31}};
s21_decimal res6 = {{MaxIntMinusOne, MaxInt, MaxInt, OneAt31}};

s21_decimal test71 = {{0b00000000000000000000001000011111, ZeroBits, ZeroBits,
                       0b00000000000000010000000000000000}};  // 54.3
s21_decimal test72 = {{0b00000000000000000000000001111011, ZeroBits, ZeroBits,
                       0b00000000000000100000000000000000}};  // 1.23
s21_decimal res7 = {{0b00000000000000000001010110110001, ZeroBits, ZeroBits,
                     0b00000000000000100000000000000000}};  // 55.53

// SUB
s21_decimal test81 = {{MaxInt, ZeroBits, ZeroBits, OneAt31}};
s21_decimal test82 = {{OneAt0, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal res8 = {{MaxIntMinusOne, ZeroBits, ZeroBits, OneAt31}};

s21_decimal test91 = {{0b00000000000000000000001000011111, ZeroBits, ZeroBits,
                       0b00000000000000010000000000000000}};  // 54.3
s21_decimal test92 = {{0b00000000000000000000000001111011, ZeroBits, ZeroBits,
                       0b10000000000000100000000000000000}};  // -1.23
s21_decimal res9 = {{0b00000000000000000001010010111011, ZeroBits, ZeroBits,
                     0b00000000000000100000000000000000}};  // 53.07

s21_decimal test101 = {{0b11100100101000001010111110110001,
                        0b00000000000000000000000000010110, ZeroBits,
                        0b10000000000010000000000000000000}};  // -983.25016497
s21_decimal test102 = {{0b00000000000000001101010101011001, ZeroBits, ZeroBits,
                        0b00000000000000110000000000000000}};  // 54.617
s21_decimal res10 = {{0b10011111000101011100001000010001,
                      0b00000000000000000000000000010101, ZeroBits,
                      0b10000000000010000000000000000000}};  // -928.63316497

s21_decimal test111 = {{MaxInt, ZeroBits, ZeroBits, OneAt31}};
s21_decimal test112 = {{MaxInt, ZeroBits, ZeroBits, ZeroBits}};
s21_decimal res11 = {{ZeroBits, ZeroBits, ZeroBits, ZeroBits}};

START_TEST(add) {
  int overload = s21_add(test1, test1, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res1, temp_res));
  ck_assert_int_eq(1, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_add(test21, test22, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res2, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_add(test31, test32, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res3, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_add(test41, test42, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res4, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_add(test51, test52, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res5, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_add(test61, test62, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res6, temp_res));
  ck_assert_int_eq(2, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_add(test71, test72, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res7, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);
}
END_TEST

START_TEST(sub) {
  int overload = s21_sub(test81, test82, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res8, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_sub(test91, test92, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res9, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_sub(test101, test102, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res10, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);

  overload = s21_sub(test111, test112, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res11, temp_res));
  ck_assert_int_eq(0, overload);
  s21_initDecimal(ZeroBits, ZeroBits, ZeroBits, ZeroBits, &temp_res);
}
END_TEST

START_TEST(is_less) {
  ck_assert_int_eq(1, s21_is_less(middle, max));
  ck_assert_int_eq(0, s21_is_less(max, middle));
  ck_assert_int_eq(1, s21_is_less(middle_fractions, middle));
  ck_assert_int_eq(1, s21_is_less(middle_minus, middle));
  ck_assert_int_eq(0, s21_is_less(null_minus, null));
}
END_TEST

START_TEST(is_less_or_equal) {
  ck_assert_int_eq(0, s21_is_less_or_equal(middle, null));
  ck_assert_int_eq(1, s21_is_less_or_equal(middle_minus, null));
  ck_assert_int_eq(1, s21_is_less_or_equal(max_minus, middle));
  ck_assert_int_eq(0, s21_is_less_or_equal(middle, middle_fractions));
  ck_assert_int_eq(1, s21_is_less_or_equal(null, null_minus));
}
END_TEST

START_TEST(is_greater) {
  ck_assert_int_eq(1, s21_is_greater(middle, null));
  ck_assert_int_eq(0, s21_is_greater(middle, max));
  ck_assert_int_eq(1, s21_is_greater(middle, max_minus));
  ck_assert_int_eq(1, s21_is_greater(middle_fractions, middle_minus));
  ck_assert_int_eq(0, s21_is_greater(middle_minus, null));
}
END_TEST

/*
START_TEST(is_greater_or_equal) {
  ck_assert_int_eq(1, s21_is_greater_or_equal(max, middle));
  ck_assert_int_eq(0, s21_is_greater_or_equal(middle, max));
  ck_assert_int_eq(1, s21_is_greater_or_equal(null, max_minus));
  ck_assert_int_eq(0, s21_is_greater_or_equal(middle_fractions, middle));
  ck_assert_int_eq(1, s21_is_greater_or_equal(null_minus, null));
}
END_TEST
*/
START_TEST(is_equal) {
  ck_assert_int_eq(0, s21_is_equal(middle, max));
  ck_assert_int_eq(0, s21_is_equal(middle, middle_fractions));
  ck_assert_int_eq(1, s21_is_equal(null, null_minus));
}
END_TEST

START_TEST(is_not_equal) {
  ck_assert_int_eq(1, s21_is_not_equal(middle, middle_fractions));
  ck_assert_int_eq(1, s21_is_not_equal(middle, max));
  ck_assert_int_eq(0, s21_is_not_equal(null, null_minus));
}
END_TEST

START_TEST(mul) {
  int output = s21_mul(middle_fractions, middle_fractions, &temp_res);
  ck_assert_int_eq(
      1, s21_is_equal(res_middle_fraction_mul_middle_fraction, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_mul(middle_fractions, null, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(null, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_mul(middle_fractions, middle_fractions_minus, &temp_res);
  ck_assert_int_eq(
      1, s21_is_equal(res_middle_fraction_mul_middle_fraction_minus, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_mul(middle, middle, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(null, temp_res));
  ck_assert_int_eq(1, output);
  output = s21_mul(middle_minus, middle, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(null, temp_res));
  ck_assert_int_eq(2, output);
}
END_TEST
/////////////////////

// START_TEST(from_decimal_to_float) {
// }
// END_TEST

/////////////////////////
/*
START_TEST(div) {
  int output = s21_div(max, middle, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_max_div_middle, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_div(middle, max, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_middle_div_max, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_div(max, null, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(null, temp_res));
  ck_assert_int_eq(3, output);
  output = s21_div(max_minus, middle, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_max_minus_div_middle, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_div(max, middle_minus, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_max_minus_div_middle, temp_res));
  ck_assert_int_eq(0, output);
}
END_TEST
*/

START_TEST(from_int_to_decimal_decimal_to_int) {
  int res = 0;
  int temp_plus = 2147483647;
  int temp_minus = -2147483647;
  int output = s21_from_int_to_decimal(temp_plus, &temp_res);
  ck_assert_int_eq(0, output);
  output = s21_from_decimal_to_int(temp_res, &res);
  ck_assert_int_eq(temp_plus, res);
  ck_assert_int_eq(0, output);
  output = s21_from_int_to_decimal(temp_minus, &temp_res);
  ck_assert_int_eq(0, output);
  output = s21_from_decimal_to_int(temp_res, &res);
  ck_assert_int_eq(temp_minus, res);
  ck_assert_int_eq(0, output);
}
END_TEST

START_TEST(from_float_to_decimal_decimal_to_float) {
  float res = 0;
  float temp_plus = 2147483.647;
  float temp_minus = -2147483.647;
  float res_plus = 2147484.;
  float res_minus = -2147484.0;

  int output = s21_from_float_to_decimal(temp_plus, &temp_res);
  ck_assert_int_eq(0, output);
  output = s21_from_decimal_to_float(temp_res, &res);
  ck_assert_float_eq(res_plus, res);
  ck_assert_int_eq(0, output);
  output = s21_from_float_to_decimal(temp_minus, &temp_res);
  ck_assert_int_eq(0, output);
  output = s21_from_decimal_to_float(temp_res, &res);
  ck_assert_float_eq(res_minus, res);
  ck_assert_int_eq(0, output);
  output = s21_from_float_to_decimal((temp_plus * 10), &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_from_float_to_decimal, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_from_decimal_to_float(tmp_float, &res);
  ck_assert_float_eq(21474840.0, res);
  ck_assert_int_eq(0, output);
}
END_TEST

START_TEST(floor_) {
  int output = s21_floor(middle_fractions, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_floor_middle_fractions, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_floor(middle_fractions_minus, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_floor_middle_fractions_minus, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_floor(floor_num, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_floor, temp_res));
  ck_assert_int_eq(0, output);
}
END_TEST

START_TEST(round_) {
  int output = s21_round(middle_fractions, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_floor_middle_fractions, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_round(middle_fractions_minus, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_round_middle_fractions_minus, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_round(round_num, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_round, temp_res));
  ck_assert_int_eq(0, output);
}
END_TEST

START_TEST(truncate) {
  int output = s21_truncate(middle_fractions, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_floor_middle_fractions, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_truncate(middle_fractions_minus, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(res_round_middle_fractions_minus, temp_res));
  ck_assert_int_eq(0, output);
}
END_TEST

START_TEST(negate) {
  int output = s21_negate(max_minus, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(max, temp_res));
  ck_assert_int_eq(0, output);
  output = s21_negate(max, &temp_res);
  ck_assert_int_eq(1, s21_is_equal(max_minus, temp_res));
  ck_assert_int_eq(0, output);
}
END_TEST

int main() {
  Suite *s = suite_create("Suite");
  TCase *tc = tcase_create("Test case");
  SRunner *sr = srunner_create(s);
  int output;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, add);
  tcase_add_test(tc, sub);

  tcase_add_test(tc, mul);
  //   tcase_add_test(tc, div);
  tcase_add_test(tc, floor_);
  tcase_add_test(tc, round_);
  tcase_add_test(tc, negate);
  tcase_add_test(tc, truncate);
  tcase_add_test(tc, is_less);
  tcase_add_test(tc, is_equal);
  tcase_add_test(tc, is_greater);
  tcase_add_test(tc, is_not_equal);
  tcase_add_test(tc, is_less_or_equal);
  //   tcase_add_test(tc, is_greater_or_equal);
  tcase_add_test(tc, from_int_to_decimal_decimal_to_int);
  tcase_add_test(tc, from_float_to_decimal_decimal_to_float);
  //   tcase_add_test(tc, from_decimal_to_float);
  //   tcase_add_test(tc, from_decimal_to_int);

  srunner_run_all(sr, CK_VERBOSE);
  output = srunner_ntests_failed(sr);
  srunner_free(sr);

  return output;
}
