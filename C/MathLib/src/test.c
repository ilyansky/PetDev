#include <check.h>

#include "s21_math.h"

// 1 ABS
START_TEST(abs_test) {
  ck_assert_int_eq(abs(5), s21_abs(5));
  ck_assert_int_eq(abs(1300), s21_abs(1300));
  ck_assert_int_eq(abs(0), s21_abs(0));
  ck_assert_int_eq(abs(-0), s21_abs(-0));
  ck_assert_int_eq(abs(INT_MAX), s21_abs(INT_MAX));
  ck_assert_int_eq(abs(INT_MIN), s21_abs(INT_MIN));
  ck_assert_int_eq(abs(-126354), s21_abs(-126354));
  ck_assert_int_eq(abs(-412341234), s21_abs(-412341234));
}
END_TEST

// 2 ASIN
START_TEST(asin_test) {
  ck_assert_ldouble_nan(asin(S21_NAN));
  ck_assert_ldouble_nan(s21_asin(S21_NAN));

  ck_assert_ldouble_nan(asin(POS_INF));
  ck_assert_ldouble_nan(s21_asin(POS_INF));

  ck_assert_ldouble_nan(asin(NEG_INF));
  ck_assert_ldouble_nan(s21_asin(NEG_INF));

  ck_assert_ldouble_nan(asin(-123));
  ck_assert_ldouble_nan(s21_asin(-123));

  ck_assert_ldouble_nan(asin(123));
  ck_assert_ldouble_nan(s21_asin(123));

  ck_assert_ldouble_nan(asin(12345.123456));
  ck_assert_ldouble_nan(s21_asin(12345.123456));

  ck_assert_ldouble_nan(asin(-12345.123456));
  ck_assert_ldouble_nan(s21_asin(-12345.123456));

  ck_assert_ldouble_eq_tol(asin(0), s21_asin(0), TOL);
  ck_assert_ldouble_eq_tol(asin(-0), s21_asin(-0), TOL);
  ck_assert_ldouble_eq_tol(asin(1.0), s21_asin(1.0), TOL);
  ck_assert_ldouble_eq_tol(asin(-1.0), s21_asin(-1.0), TOL);
  ck_assert_ldouble_eq_tol(asin(-1), s21_asin(-1), TOL);
  ck_assert_ldouble_eq_tol(asin(1), s21_asin(1), TOL);
  ck_assert_ldouble_eq_tol(asin(-0.9999), s21_asin(-0.9999), TOL);
  ck_assert_ldouble_eq_tol(asin(0.847150), s21_asin(0.847150), TOL);
  ck_assert_ldouble_eq_tol(asin(0.156), s21_asin(0.156), TOL);
}
END_TEST

// 3 ACOS
START_TEST(acos_test) {
  ck_assert_ldouble_nan(acos(S21_NAN));
  ck_assert_ldouble_nan(s21_acos(S21_NAN));

  ck_assert_ldouble_nan(acos(POS_INF));
  ck_assert_ldouble_nan(s21_acos(POS_INF));

  ck_assert_ldouble_nan(acos(NEG_INF));
  ck_assert_ldouble_nan(s21_acos(NEG_INF));

  ck_assert_ldouble_nan(acos(-123));
  ck_assert_ldouble_nan(s21_acos(-123));

  ck_assert_ldouble_nan(acos(123));
  ck_assert_ldouble_nan(s21_acos(123));

  ck_assert_ldouble_nan(acos(12345.123456));
  ck_assert_ldouble_nan(s21_acos(12345.123456));

  ck_assert_ldouble_nan(acos(-12345.123456));
  ck_assert_ldouble_nan(s21_acos(-12345.123456));

  ck_assert_ldouble_eq_tol(acos(0), s21_acos(0), TOL);
  ck_assert_ldouble_eq_tol(acos(-1), s21_acos(-1), TOL);
  ck_assert_ldouble_eq_tol(acos(1), s21_acos(1), TOL);
  ck_assert_ldouble_eq_tol(acos(-0.9999), s21_acos(-0.9999), TOL);
  ck_assert_ldouble_eq_tol(acos(0.847150), s21_acos(0.847150), TOL);
  ck_assert_ldouble_eq_tol(acos(0.369), s21_acos(0.369), TOL);
}
END_TEST

// 4 ATAN
START_TEST(atan_test) {
  ck_assert_ldouble_eq_tol(atan(POS_INF), s21_atan(POS_INF), TOL);
  ck_assert_ldouble_eq_tol(atan(NEG_INF), s21_atan(NEG_INF), TOL);
  ck_assert_ldouble_eq_tol(atan(-25.12345), s21_atan(-25.12345), TOL);
  ck_assert_ldouble_eq_tol(atan(0.23464), s21_atan(0.23464), TOL);
  ck_assert_ldouble_eq_tol(atan(0), s21_atan(0), TOL);
  ck_assert_ldouble_eq_tol(atan(-0), s21_atan(-0), TOL);
  ck_assert_ldouble_eq_tol(atan(12345.123456), s21_atan(12345.123456), TOL);
  ck_assert_ldouble_eq_tol(atan(-12345.123456), s21_atan(-12345.123456), TOL);
  ck_assert_ldouble_eq_tol(atan(21.42), s21_atan(21.42), TOL);
  ck_assert_ldouble_eq_tol(atan(-123), s21_atan(-123), TOL);
  ck_assert_ldouble_eq_tol(atan(3.12365), s21_atan(3.12365), TOL);
  ck_assert_ldouble_eq_tol(atan(500), s21_atan(500), TOL);
  ck_assert_ldouble_eq_tol(atan(14.96), s21_atan(14.96), TOL);
  ck_assert_ldouble_eq_tol(atan(-0.93751), s21_atan(-0.93751), TOL);
  ck_assert_ldouble_eq_tol(atan(83241), s21_atan(83241), TOL);
  ck_assert_ldouble_eq_tol(atan(-918275), s21_atan(-918275), TOL);
  ck_assert_ldouble_eq_tol(atan(-918275.929), s21_atan(-918275.929), TOL);

  ck_assert_ldouble_nan(atan(S21_NAN));
  ck_assert_ldouble_nan(s21_atan(S21_NAN));
}
END_TEST

// 5 CEIL
START_TEST(ceil_test) {
  ck_assert_ldouble_eq(ceil(POS_INF), s21_ceil(POS_INF));
  ck_assert_ldouble_eq(ceil(NEG_INF), s21_ceil(NEG_INF));
  ck_assert_ldouble_eq(ceil(-LDBL_MAX), s21_ceil(-LDBL_MAX));
  ck_assert_ldouble_eq(ceil(LDBL_MAX), s21_ceil(LDBL_MAX));
  ck_assert_ldouble_eq_tol(ceil(5), s21_ceil(5), TOL);
  ck_assert_ldouble_eq_tol(ceil(-1300.999999), s21_ceil(-1300.999999), TOL);
  ck_assert_ldouble_eq_tol(ceil(1300.999999), s21_ceil(1300.999999), TOL);
  ck_assert_ldouble_eq_tol(ceil(0), s21_ceil(0), TOL);
  ck_assert_ldouble_eq_tol(ceil(456.3), s21_ceil(456.3), TOL);
  ck_assert_ldouble_eq_tol(ceil(-6325.12), s21_ceil(-6325.12), TOL);
  ck_assert_ldouble_eq_tol(ceil(-12345.0), s21_ceil(-12345.0), TOL);
  ck_assert_ldouble_eq_tol(ceil(12345.0), s21_ceil(12345.0), TOL);
  ck_assert_ldouble_eq_tol(ceil(-12345.124567), s21_ceil(-12345.124567), TOL);
  ck_assert_ldouble_eq_tol(ceil(12345.124567), s21_ceil(12345.124567), TOL);

  ck_assert_ldouble_nan(ceil(S21_NAN));
  ck_assert_ldouble_nan(s21_ceil(S21_NAN));
}
END_TEST

// 6 COS
START_TEST(cos_test) {
  ck_assert_ldouble_eq_tol(cos(30 * TO_RAD), s21_cos(30 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(45 * TO_RAD), s21_cos(45 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(60 * TO_RAD), s21_cos(60 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(90 * TO_RAD), s21_cos(90 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(150 * TO_RAD), s21_cos(150 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(180 * TO_RAD), s21_cos(180 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(270 * TO_RAD), s21_cos(270 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(300.123654), s21_cos(300.123654), TOL);
  ck_assert_ldouble_eq_tol(cos(315 * TO_RAD), s21_cos(315 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(330 * TO_RAD), s21_cos(330 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(360 * TO_RAD), s21_cos(360 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(cos(0.45), s21_cos(0.45), TOL);
  ck_assert_ldouble_eq_tol(cos(S21_PI), s21_cos(S21_PI), TOL);
  ck_assert_ldouble_eq_tol(cos(0), s21_cos(0), TOL);
  ck_assert_ldouble_eq_tol(cos(-0), s21_cos(-0), TOL);
  ck_assert_ldouble_eq_tol(cos(1.0), s21_cos(1.0), TOL);
  ck_assert_ldouble_eq_tol(cos(-1.0), s21_cos(-1.0), TOL);

  ck_assert_ldouble_eq_tol(cos(45), s21_cos(45), TOL);
  ck_assert_ldouble_eq_tol(cos(360), s21_cos(360), TOL);
  ck_assert_ldouble_eq_tol(cos(1234), s21_cos(1234), TOL);
  ck_assert_ldouble_eq_tol(cos(73624235), s21_cos(73624235), TOL);
  ck_assert_ldouble_eq_tol(cos(38357234), s21_cos(38357234), TOL);
  ck_assert_ldouble_eq_tol(cos(-127875643), s21_cos(-127875643), TOL);
  ck_assert_ldouble_eq_tol(cos(38357234.43264), s21_cos(38357234.43264), TOL);
  ck_assert_ldouble_eq_tol(cos(-127875643.935723), s21_cos(-127875643.935723),
                           TOL);

  ck_assert_ldouble_nan(cos(POS_INF));
  ck_assert_ldouble_nan(s21_cos(POS_INF));

  ck_assert_ldouble_nan(cos(NEG_INF));
  ck_assert_ldouble_nan(s21_cos(NEG_INF));

  ck_assert_ldouble_nan(cos(S21_NAN));
  ck_assert_ldouble_nan(s21_cos(S21_NAN));
}
END_TEST

// 7 EXP
START_TEST(exp_test) {
  ck_assert_ldouble_eq(exp(POS_INF), s21_exp(POS_INF));
  ck_assert_ldouble_eq(exp(NEG_INF), s21_exp(NEG_INF));
  ck_assert_ldouble_eq_tol(exp(-123.935723), s21_exp(-123.935723), TOL);
  ck_assert_ldouble_eq_tol(exp(5), s21_exp(5), TOL);
  ck_assert_ldouble_eq_tol(exp(-130.999999), s21_exp(-130.999999), TOL);
  ck_assert_ldouble_eq_tol(exp(0), s21_exp(0), TOL);
  ck_assert_ldouble_eq_tol(exp(-6325.12), s21_exp(-6325.12), TOL);
  ck_assert_ldouble_eq_tol(exp(-0), s21_exp(-0), TOL);
  ck_assert_ldouble_eq_tol(exp(-1.0), s21_exp(-1.0), TOL);
  ck_assert_ldouble_eq_tol(exp(1.0), s21_exp(1.0), TOL);
  ck_assert_ldouble_eq_tol(exp(2.0), s21_exp(2.0), TOL);
  ck_assert_ldouble_eq_tol(exp(21.12356), s21_exp(21.12356), TOL);
  ck_assert_ldouble_eq_tol(exp(-21.12356), s21_exp(-21.12356), TOL);

  ck_assert_ldouble_nan(exp(S21_NAN));
  ck_assert_ldouble_nan(s21_exp(S21_NAN));
}
END_TEST

// 8 FABS
START_TEST(fabs_test) {
  ck_assert_ldouble_eq_tol(fabs(5.000000), s21_fabs(5.000000), TOL);
  ck_assert_ldouble_eq_tol(fabs(0.0), s21_fabs(0.0), TOL);
  ck_assert_ldouble_eq_tol(fabs(-1300.342356), s21_fabs(-1300.342356), TOL);
  ck_assert_ldouble_eq_tol(fabs(0.123456), s21_fabs(0.123456), TOL);
  ck_assert_ldouble_eq_tol(fabs(-0.654321), s21_fabs(-0.654321), TOL);
  ck_assert_ldouble_eq_tol(fabs(-412341234.123000), s21_fabs(-412341234.123000),
                           TOL);
  ck_assert_ldouble_eq(fabs(POS_INF), s21_fabs(POS_INF));
  ck_assert_ldouble_eq(fabs(NEG_INF), s21_fabs(NEG_INF));
  ck_assert_ldouble_eq(fabs(DBL_MAX), s21_fabs(DBL_MAX));
  ck_assert_ldouble_eq(fabs(DBL_MAX - 1), s21_fabs(DBL_MAX - 1));
  ck_assert_ldouble_eq(fabs(DBL_MIN), s21_fabs(DBL_MIN));

  ck_assert_ldouble_nan(fabs(S21_NAN));
  ck_assert_ldouble_nan(s21_fabs(S21_NAN));
}
END_TEST

// 9 FLOOR
START_TEST(floor_test) {
  ck_assert_ldouble_eq_tol(floor(5), s21_floor(5), TOL);
  ck_assert_ldouble_eq_tol(floor(-1300.999999), s21_floor(-1300.999999), TOL);
  ck_assert_ldouble_eq_tol(floor(1300.999999), s21_floor(1300.999999), TOL);
  ck_assert_ldouble_eq_tol(floor(0), s21_floor(0), TOL);
  ck_assert_ldouble_eq_tol(floor(456.3), s21_floor(456.3), TOL);
  ck_assert_ldouble_eq_tol(floor(-6325.12), s21_floor(-6325.12), TOL);
  ck_assert_ldouble_eq_tol(floor(-6), s21_floor(-6), TOL);
  ck_assert_ldouble_eq(floor(POS_INF), s21_floor(POS_INF));
  ck_assert_ldouble_eq(floor(NEG_INF), s21_floor(NEG_INF));
  ck_assert_ldouble_eq(floor(DBL_MAX), s21_floor(DBL_MAX));
  ck_assert_ldouble_eq(floor(DBL_MAX - 1), s21_floor(DBL_MAX - 1));
  ck_assert_ldouble_eq(floor(DBL_MIN), s21_floor(DBL_MIN));

  ck_assert_ldouble_nan(floor(S21_NAN));
  ck_assert_ldouble_nan(s21_floor(S21_NAN));
}
END_TEST

// 10 FMOD
START_TEST(fmod_test) {
  ck_assert_ldouble_eq_tol(fmod(-14503.123, -8361.2345),
                           s21_fmod(-14503.123, -8361.2345), TOL);
  ck_assert_ldouble_eq_tol(fmod(14503.123, 8361.2345),
                           s21_fmod(14503.123, 8361.2345), TOL);
  ck_assert_ldouble_eq_tol(fmod(14503.123, -761.2345),
                           s21_fmod(14503.123, -761.2345), TOL);
  ck_assert_ldouble_eq_tol(fmod(-54303.123, 51.234615),
                           s21_fmod(-54303.123, 51.234615), TOL);
  ck_assert_ldouble_eq_tol(fmod(-4971.0986, -1526376.1725),
                           s21_fmod(-4971.0986, -1526376.1725), TOL);
  ck_assert_ldouble_eq_tol(fmod(49171.03986, 1528376.1725),
                           s21_fmod(49171.03986, 1528376.1725), TOL);
  ck_assert_ldouble_eq_tol(fmod(49171.03986, -1528376.1725),
                           s21_fmod(49171.03986, -1528376.1725), TOL);
  ck_assert_ldouble_eq_tol(fmod(-49171.03986, 6528376.1725),
                           s21_fmod(-49171.03986, 6528376.1725), TOL);
  ck_assert_ldouble_eq_tol(fmod(-49171.03986, -49171.03986),
                           s21_fmod(-49171.03986, -49171.03986), TOL);
  ck_assert_ldouble_eq_tol(fmod(823647.261246, 823647.261246),
                           s21_fmod(823647.261246, 823647.261246), TOL);
  ck_assert_ldouble_eq_tol(fmod(923647.261246, -923647.261246),
                           s21_fmod(923647.261246, -923647.261246), TOL);
  ck_assert_ldouble_eq_tol(fmod(0, -1263.1234), s21_fmod(0, -1263.1234), TOL);
  ck_assert_ldouble_eq_tol(fmod(0, 1263.1234), s21_fmod(0, 1263.1234), TOL);
  ck_assert_ldouble_eq_tol(fmod(-0, -1263.1234), s21_fmod(-0, -1263.1234), TOL);
  ck_assert_ldouble_eq_tol(fmod(-0, 1263.1234), s21_fmod(-0, 1263.1234), TOL);
  ck_assert_ldouble_eq_tol(fmod(27346, 7567), s21_fmod(27346, 7567), TOL);
  ck_assert_ldouble_eq_tol(fmod(654, 12456), s21_fmod(654, 12456), TOL);
  ck_assert_ldouble_eq_tol(fmod(-127346, -723), s21_fmod(-127346, -723), TOL);
  ck_assert_ldouble_eq_tol(fmod(-127, -76481313), s21_fmod(-127, -76481313),
                           TOL);
  ck_assert_ldouble_eq_tol(fmod(-127346, 723), s21_fmod(-127346, 723), TOL);
  ck_assert_ldouble_eq_tol(fmod(-127, 76481313), s21_fmod(-127, 76481313), TOL);
  ck_assert_ldouble_eq(fmod(123, NEG_INF), s21_fmod(123, NEG_INF));
  ck_assert_ldouble_eq(fmod(123, POS_INF), s21_fmod(123, POS_INF));

  ck_assert_ldouble_nan(fmod(0, 0));
  ck_assert_ldouble_nan(s21_fmod(0, 0));

  ck_assert_ldouble_nan(fmod(-0, -0));
  ck_assert_ldouble_nan(s21_fmod(-0, -0));

  ck_assert_ldouble_nan(fmod(-0, 0));
  ck_assert_ldouble_nan(s21_fmod(-0, 0));

  ck_assert_ldouble_nan(fmod(0, -0));
  ck_assert_ldouble_nan(s21_fmod(0, -0));

  ck_assert_ldouble_nan(fmod(31273.123, 0));
  ck_assert_ldouble_nan(s21_fmod(31273.123, 0));

  ck_assert_ldouble_nan(fmod(-12746.96834, 0));
  ck_assert_ldouble_nan(s21_fmod(-12746.96834, 0));

  ck_assert_ldouble_nan(fmod(-924552, -0));
  ck_assert_ldouble_nan(s21_fmod(-924552, -0));

  ck_assert_ldouble_nan(fmod(POS_INF, NEG_INF));
  ck_assert_ldouble_nan(s21_fmod(POS_INF, NEG_INF));

  ck_assert_ldouble_nan(fmod(NEG_INF, POS_INF));
  ck_assert_ldouble_nan(s21_fmod(NEG_INF, POS_INF));

  ck_assert_ldouble_nan(fmod(S21_NAN, POS_INF));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, POS_INF));

  ck_assert_ldouble_nan(fmod(S21_NAN, NEG_INF));
  ck_assert_ldouble_nan(s21_fmod(S21_NAN, NEG_INF));

  ck_assert_ldouble_nan(fmod(POS_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(POS_INF, S21_NAN));

  ck_assert_ldouble_nan(fmod(NEG_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_fmod(NEG_INF, S21_NAN));

  ck_assert_ldouble_nan(fmod(POS_INF, 123));
  ck_assert_ldouble_nan(s21_fmod(POS_INF, 123));
}
END_TEST

// 11 LOG
START_TEST(log_test) {
  ck_assert_ldouble_eq_tol(log(26941.289), s21_log(26941.289), TOL);
  ck_assert_ldouble_eq(log(POS_INF), s21_log(POS_INF));
  ck_assert_ldouble_eq(log(0), s21_log(0));
  ck_assert_ldouble_eq_tol(log(1), s21_log(1), TOL);
  ck_assert_ldouble_eq_tol(log(18749363), s21_log(18749363), TOL);

  ck_assert_ldouble_nan(log(-12.36));
  ck_assert_ldouble_nan(s21_log(-12.36));

  ck_assert_ldouble_nan(log(NEG_INF));
  ck_assert_ldouble_nan(s21_log(NEG_INF));

  ck_assert_ldouble_nan(log(S21_NAN));
  ck_assert_ldouble_nan(s21_log(S21_NAN));

  ck_assert_ldouble_nan(log(-86.82357));
  ck_assert_ldouble_nan(s21_log(-86.82357));

  ck_assert_ldouble_nan(log(-21341));
  ck_assert_ldouble_nan(s21_log(-21341));

  ck_assert_ldouble_nan(log(-1));
  ck_assert_ldouble_nan(s21_log(-1));
}
END_TEST

// 12 POW
START_TEST(pow_test) {
  ck_assert_ldouble_eq_tol(pow(0, 0), s21_pow(0, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(0, 1), s21_pow(0, 1), TOL);
  ck_assert_ldouble_eq_tol(pow(0, 0), s21_pow(0, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(0, POS_INF), s21_pow(0, POS_INF), TOL);
  ck_assert_double_eq_tol(pow(-1, POS_INF), s21_pow(-1, POS_INF), TOL);
  ck_assert_double_eq_tol(pow(-1, NEG_INF), s21_pow(-1, NEG_INF), TOL);
  ck_assert_ldouble_eq_tol(pow(1, S21_NAN), s21_pow(1, S21_NAN), TOL);
  ck_assert_ldouble_eq_tol(pow(1, POS_INF), s21_pow(1, POS_INF), TOL);
  ck_assert_ldouble_eq_tol(pow(1, NEG_INF), s21_pow(1, NEG_INF), TOL);
  ck_assert_ldouble_eq_tol(pow(1, 0), s21_pow(1, 0), TOL);
  ck_assert_ldouble_eq(pow(0, -100), s21_pow(0, -100));
  ck_assert_ldouble_eq(pow(0, NEG_INF), s21_pow(0, NEG_INF));
  ck_assert_ldouble_eq_tol(pow(1, 123), s21_pow(1, 123), TOL);
  ck_assert_ldouble_eq_tol(pow(S21_NAN, 0), s21_pow(S21_NAN, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(POS_INF, 0), s21_pow(POS_INF, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(NEG_INF, 0), s21_pow(NEG_INF, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(123, 0), s21_pow(123, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(0.999999, POS_INF), s21_pow(0.999999, POS_INF),
                           TOL);
  ck_assert_ldouble_eq(pow(0.345987, NEG_INF), s21_pow(0.345987, NEG_INF));
  ck_assert_ldouble_eq(pow(12, POS_INF), s21_pow(12, POS_INF));
  ck_assert_ldouble_eq_tol(pow(98, NEG_INF), s21_pow(98, NEG_INF), TOL);
  ck_assert_ldouble_eq_tol(pow(POS_INF, 0), s21_pow(POS_INF, 0), TOL);
  ck_assert_ldouble_eq_tol(pow(NEG_INF, 0), s21_pow(NEG_INF, 0), TOL);
  ck_assert_ldouble_eq(pow(POS_INF, 6450), s21_pow(POS_INF, 6450));
  ck_assert_ldouble_eq(pow(NEG_INF, 6450), s21_pow(NEG_INF, 6450));
  ck_assert_ldouble_eq(pow(POS_INF, POS_INF), s21_pow(POS_INF, POS_INF));
  ck_assert_ldouble_eq(pow(NEG_INF, POS_INF), s21_pow(NEG_INF, POS_INF));
  ck_assert_ldouble_eq_tol(pow(POS_INF, NEG_INF), s21_pow(POS_INF, NEG_INF),
                           TOL);
  ck_assert_ldouble_eq_tol(pow(NEG_INF, NEG_INF), s21_pow(NEG_INF, NEG_INF),
                           TOL);
  ck_assert_ldouble_eq_tol(pow(5.12423, 3.126734), s21_pow(5.12423, 3.126734),
                           TOL);
  ck_assert_ldouble_eq_tol(pow(5.12423, -3.126734), s21_pow(5.12423, -3.126734),
                           TOL);

  ck_assert_ldouble_nan(pow(0, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(0, S21_NAN));

  ck_assert_ldouble_nan(pow(0, -S21_NAN));
  ck_assert_ldouble_nan(s21_pow(0, -S21_NAN));

  ck_assert_ldouble_nan(pow(POS_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(POS_INF, S21_NAN));

  ck_assert_ldouble_nan(pow(NEG_INF, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(NEG_INF, S21_NAN));

  ck_assert_ldouble_nan(pow(S21_NAN, S21_NAN));
  ck_assert_ldouble_nan(s21_pow(S21_NAN, S21_NAN));

  ck_assert_ldouble_nan(pow(-5.12423, -3.126734));
  ck_assert_ldouble_nan(s21_pow(-5.12423, -3.126734));

  ck_assert_ldouble_nan(pow(-5.12423, 3.126734));
  ck_assert_ldouble_nan(s21_pow(-5.12423, 3.126734));
}
END_TEST

// 13 SIN
START_TEST(sin_test) {
  ck_assert_ldouble_eq_tol(sin(30 * TO_RAD), s21_sin(30 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(45 * TO_RAD), s21_sin(45 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(60 * TO_RAD), s21_sin(60 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(90 * TO_RAD), s21_sin(90 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(150 * TO_RAD), s21_sin(150 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(180 * TO_RAD), s21_sin(180 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(270 * TO_RAD), s21_sin(270 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(300.123654), s21_sin(300.123654), TOL);
  ck_assert_ldouble_eq_tol(sin(315 * TO_RAD), s21_sin(315 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(330 * TO_RAD), s21_sin(330 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(360 * TO_RAD), s21_sin(360 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(sin(0.45), s21_sin(0.45), TOL);
  ck_assert_ldouble_eq_tol(sin(S21_PI), s21_sin(S21_PI), TOL);
  ck_assert_ldouble_eq_tol(sin(0), s21_sin(0), TOL);
  ck_assert_ldouble_eq_tol(sin(-0), s21_sin(-0), TOL);
  ck_assert_ldouble_eq_tol(sin(1.0), s21_sin(1.0), TOL);
  ck_assert_ldouble_eq_tol(sin(-1.0), s21_sin(-1.0), TOL);

  ck_assert_ldouble_eq_tol(sin(45), s21_sin(45), TOL);
  ck_assert_ldouble_eq_tol(sin(360), s21_sin(360), TOL);
  ck_assert_ldouble_eq_tol(sin(1234), s21_sin(1234), TOL);
  ck_assert_ldouble_eq_tol(sin(73624235), s21_sin(73624235), TOL);
  ck_assert_ldouble_eq_tol(sin(38357234), s21_sin(38357234), TOL);
  ck_assert_ldouble_eq_tol(sin(-127875643), s21_sin(-127875643), TOL);
  ck_assert_ldouble_eq_tol(sin(38357234.43264), s21_sin(38357234.43264), TOL);
  ck_assert_ldouble_eq_tol(sin(-127875643.935723), s21_sin(-127875643.935723),
                           TOL);

  ck_assert_ldouble_nan(sin(POS_INF));
  ck_assert_ldouble_nan(s21_sin(POS_INF));

  ck_assert_ldouble_nan(sin(NEG_INF));
  ck_assert_ldouble_nan(s21_sin(NEG_INF));

  ck_assert_ldouble_nan(sin(S21_NAN));
  ck_assert_ldouble_nan(s21_sin(S21_NAN));
}
END_TEST

// 14 SQRT
START_TEST(sqrt_test) {
  ck_assert_ldouble_nan(sqrt(-0.01));
  ck_assert_ldouble_nan(s21_sqrt(-0.01));

  ck_assert_ldouble_nan(sqrt(S21_NAN));
  ck_assert_ldouble_nan(s21_sqrt(S21_NAN));

  ck_assert_ldouble_nan(sqrt(NEG_INF));
  ck_assert_ldouble_nan(s21_sqrt(NEG_INF));

  ck_assert_ldouble_nan(sqrt(-231.41));
  ck_assert_ldouble_nan(s21_sqrt(-231.41));

  ck_assert_double_eq(sqrt(POS_INF), s21_sqrt(POS_INF));
  long double arr[] = {5898.467, 8427.928,  5698.0035, 1289.244, 7025.7,
                       12.1357,  4745.5,    2930.637,  8187.391, 1015.89,
                       3155.844, 3954.143,  2862.1,    2782.954, 5097.545,
                       2630.4,   1075.747,  1889.786,  1782,     0.0001,
                       21345678, 7432,      0.3245,    12345,    13456,
                       0.03213,  324.42342, 0,         50,       0.24};
  for (int i = 0; i < 30; i++) {
    ck_assert_double_eq_tol(sqrt(arr[i]), s21_sqrt(arr[i]), TOL);
  }

  ck_assert_ldouble_eq_tol(sqrt(623874652375.213635),
                           s21_sqrt(623874652375.213635), TOL);
}
END_TEST

// 15 TAN
START_TEST(tan_test) {
  ck_assert_ldouble_eq_tol(tan(30 * TO_RAD), s21_tan(30 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(45 * TO_RAD), s21_tan(45 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(60 * TO_RAD), s21_tan(60 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(150 * TO_RAD), s21_tan(150 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(180 * TO_RAD), s21_tan(180 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(300.123654), s21_tan(300.123654), TOL);
  ck_assert_ldouble_eq_tol(tan(315 * TO_RAD), s21_tan(315 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(330 * TO_RAD), s21_tan(330 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(360 * TO_RAD), s21_tan(360 * TO_RAD), TOL);
  ck_assert_ldouble_eq_tol(tan(0.45), s21_tan(0.45), TOL);
  ck_assert_ldouble_eq_tol(tan(S21_PI), s21_tan(S21_PI), TOL);
  ck_assert_ldouble_eq_tol(tan(0), s21_tan(0), TOL);
  ck_assert_ldouble_eq_tol(tan(-0), s21_tan(-0), TOL);
  ck_assert_ldouble_eq_tol(tan(1.0), s21_tan(1.0), TOL);
  ck_assert_ldouble_eq_tol(tan(-1.0), s21_tan(-1.0), TOL);

  ck_assert_ldouble_eq_tol(tan(45), s21_tan(45), TOL);
  ck_assert_ldouble_eq_tol(tan(360), s21_tan(360), TOL);
  ck_assert_ldouble_eq_tol(tan(1234), s21_tan(1234), TOL);
  ck_assert_ldouble_eq_tol(tan(73624235), s21_tan(73624235), TOL);
  ck_assert_ldouble_eq_tol(tan(38357234), s21_tan(38357234), TOL);
  ck_assert_ldouble_eq_tol(tan(-127875643), s21_tan(-127875643), TOL);
  ck_assert_ldouble_eq_tol(tan(38357234.43264), s21_tan(38357234.43264), TOL);
  ck_assert_ldouble_eq_tol(tan(-127875643.935723), s21_tan(-127875643.935723),
                           TOL);

  ck_assert_ldouble_nan(tan(POS_INF));
  ck_assert_ldouble_nan(s21_tan(POS_INF));

  ck_assert_ldouble_nan(tan(NEG_INF));
  ck_assert_ldouble_nan(s21_tan(NEG_INF));

  ck_assert_ldouble_nan(tan(S21_NAN));
  ck_assert_ldouble_nan(s21_tan(S21_NAN));
}
END_TEST

void tc_abs(TCase *tc) { tcase_add_test(tc, abs_test); }

void tc_ceil(TCase *tc) { tcase_add_test(tc, ceil_test); }

void tc_floor(TCase *tc) { tcase_add_test(tc, floor_test); }

void tc_cos(TCase *tc) { tcase_add_test(tc, cos_test); }

void tc_fabs(TCase *tc) { tcase_add_test(tc, fabs_test); }

void tc_pow(TCase *tc) { tcase_add_test(tc, pow_test); }

void tc_sin(TCase *tc) { tcase_add_test(tc, sin_test); }

void tc_fmod(TCase *tc) { tcase_add_test(tc, fmod_test); }

void tc_tan(TCase *tc) { tcase_add_test(tc, tan_test); }

void tc_exp(TCase *tc) { tcase_add_test(tc, exp_test); }

void tc_log(TCase *tc) { tcase_add_test(tc, log_test); }

void tc_sqrt(TCase *tc) { tcase_add_test(tc, sqrt_test); }

void tc_atan(TCase *tc) { tcase_add_test(tc, atan_test); }

void tc_asin(TCase *tc) { tcase_add_test(tc, asin_test); }

void tc_acos(TCase *tc) { tcase_add_test(tc, acos_test); }

int runner(Suite *s, TCase *tc) {
  suite_add_tcase(s, tc);
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int nfailed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nfailed;
}

int main(void) {
  Suite *s = suite_create("Suite");
  TCase *tc = tcase_create("Test case");
  tc_abs(tc);
  tc_pow(tc);
  tc_cos(tc);
  tc_sin(tc);
  tc_fabs(tc);
  tc_ceil(tc);
  tc_floor(tc);
  tc_fmod(tc);
  tc_tan(tc);
  tc_exp(tc);
  tc_log(tc);
  tc_sqrt(tc);
  tc_atan(tc);
  tc_asin(tc);
  tc_acos(tc);

  return runner(s, tc);
}
