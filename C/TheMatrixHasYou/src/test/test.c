#include <check.h>

#include "../s21_matrix.h"

void cleanTest(int *ret, int *f, matrix_t *m1, matrix_t *m2, matrix_t *c,
               matrix_t *c1) {
  *ret = 0;
  *f = 0;
  refreshMatr(m1);
  refreshMatr(m2);
  refreshMatr(c);
  refreshMatr(c1);
}

void freeMemory(matrix_t *m1, matrix_t *m2, matrix_t *m3, matrix_t *m4,
                matrix_t *m5, matrix_t *m6, matrix_t *c, matrix_t *c1,
                matrix_t *r) {
  s21_remove_matrix(r);
  s21_remove_matrix(m1);
  s21_remove_matrix(m2);
  s21_remove_matrix(m3);
  s21_remove_matrix(m4);
  s21_remove_matrix(m5);
  s21_remove_matrix(m6);
  s21_remove_matrix(c);
  s21_remove_matrix(c1);
}

matrix_t m1;
matrix_t m2;
matrix_t m3;  // error size
matrix_t m4;  // another size
matrix_t m5;  // matr size 1x1
matrix_t m6;  // matr2 size 1x1
matrix_t r;   // res
matrix_t c;   // check
matrix_t c1;  // check 1x1
matrix_t check;
int ret = 0;
int f = 0;
double result = 0.0;

START_TEST(sum) {
  s21_create_matrix(2, 4, &m1);
  s21_create_matrix(2, 4, &m2);
  s21_create_matrix(0, 4, &m3);
  s21_create_matrix(3, 4, &m4);
  s21_create_matrix(1, 1, &m5);
  s21_create_matrix(1, 1, &m6);
  s21_create_matrix(2, 4, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  ret = s21_sum_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m1, &m2, &c, &c1);
  s21_remove_matrix(&r);

  // 2
  m1.matrix[0][0] = 0.5;
  m2.matrix[0][0] = 3.0;
  c.matrix[0][0] = 3.5;

  ret = s21_sum_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m1, &m2, &c, &c1);
  s21_remove_matrix(&r);

  // 3
  m1.matrix[1][1] = -100.0;
  m2.matrix[1][1] = 5486.5;
  c.matrix[1][1] = 5386.5;

  ret = s21_sum_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m1, &m2, &c, &c1);
  s21_remove_matrix(&r);

  // 4
  ret = s21_sum_matrix(&m1, &m3, &r);
  ck_assert_int_eq(1, ret);

  cleanTest(&ret, &f, &m1, &m3, &c, &c1);

  // 5
  ret = s21_sum_matrix(&m1, &m4, &r);
  ck_assert_int_eq(2, ret);

  cleanTest(&ret, &f, &m1, &m4, &c, &c1);

  // 6
  m5.matrix[0][0] = 100.5;
  m6.matrix[0][0] = 200.999999;
  c1.matrix[0][0] = 301.499999;

  ret = s21_sum_matrix(&m5, &m6, &r);
  f = s21_eq_matrix(&r, &c1);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m5, &m6, &c, &c1);

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(sub) {
  s21_create_matrix(2, 4, &m1);
  s21_create_matrix(2, 4, &m2);
  s21_create_matrix(0, 4, &m3);
  s21_create_matrix(3, 4, &m4);
  s21_create_matrix(1, 1, &m5);
  s21_create_matrix(1, 1, &m6);
  s21_create_matrix(2, 4, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  ret = s21_sub_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m1, &m2, &c, &c1);
  s21_remove_matrix(&r);

  // 2
  m1.matrix[0][0] = 0.5;
  m2.matrix[0][0] = 3.0;
  c.matrix[0][0] = -2.5;

  ret = s21_sub_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m1, &m2, &c, &c1);
  s21_remove_matrix(&r);

  // 3
  m1.matrix[1][1] = -100.0;
  m2.matrix[1][1] = 5486.5;
  c.matrix[1][1] = -5586.5;

  ret = s21_sub_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m1, &m2, &c, &c1);
  s21_remove_matrix(&r);

  // 4
  ret = s21_sub_matrix(&m1, &m3, &r);
  ck_assert_int_eq(1, ret);

  cleanTest(&ret, &f, &m1, &m3, &c, &c1);

  // 5
  ret = s21_sub_matrix(&m1, &m4, &r);
  ck_assert_int_eq(2, ret);

  cleanTest(&ret, &f, &m1, &m4, &c, &c1);

  // 6
  m5.matrix[0][0] = 100.5;
  m6.matrix[0][0] = 200.999999;
  c1.matrix[0][0] = -100.499999;

  ret = s21_sub_matrix(&m5, &m6, &r);
  f = s21_eq_matrix(&r, &c1);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  cleanTest(&ret, &f, &m5, &m6, &c, &c1);

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(mult_num) {
  // Alloc
  s21_create_matrix(4, 8, &m1);
  s21_create_matrix(4, 8, &m2);
  s21_create_matrix(15, -3, &m3);
  s21_create_matrix(3, 4, &m4);
  s21_create_matrix(1, 1, &m5);
  s21_create_matrix(1, 1, &m6);
  s21_create_matrix(4, 8, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  // Init
  m1.matrix[3][5] = 5.0;
  c.matrix[3][5] = 25.0;

  // Calc
  ret = s21_mult_number(&m1, 5.0, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  // Refresh
  ret = 0;
  f = 0;
  refreshMatr(&m1);
  refreshMatr(&c);
  s21_remove_matrix(&r);

  // 2
  ret = s21_mult_number(&m3, 8.3, &r);
  ck_assert_int_eq(1, ret);

  ret = 0;

  // 3
  m1.matrix[2][1] = -1234.23;
  c.matrix[2][1] = -10244.109;

  ret = s21_mult_number(&m1, 8.3, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  ret = 0;
  f = 0;

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(mult) {
  // Alloc
  s21_create_matrix(3, 2, &m1);
  s21_create_matrix(2, 3, &m2);
  s21_create_matrix(15, -3, &m3);
  s21_create_matrix(3, 1, &m4);
  s21_create_matrix(1, 3, &m5);
  s21_create_matrix(1, 1, &m6);
  s21_create_matrix(3, 3, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  // Init
  m1.matrix[0][0] = 1.0;
  m1.matrix[0][1] = 4.0;
  m1.matrix[1][0] = 2.0;
  m1.matrix[1][1] = 5.0;
  m1.matrix[2][0] = 3.0;
  m1.matrix[2][1] = 6.0;

  m2.matrix[0][0] = 1.0;
  m2.matrix[0][1] = -1.0;
  m2.matrix[0][2] = 1.0;
  m2.matrix[1][0] = 2.0;
  m2.matrix[1][1] = 3.0;
  m2.matrix[1][2] = 4.0;

  c.matrix[0][0] = 9.0;
  c.matrix[0][1] = 11.0;
  c.matrix[0][2] = 17.0;
  c.matrix[1][0] = 12.0;
  c.matrix[1][1] = 13.0;
  c.matrix[1][2] = 22.0;
  c.matrix[2][0] = 15.0;
  c.matrix[2][1] = 15.0;
  c.matrix[2][2] = 27.0;

  ret = s21_mult_matrix(&m1, &m2, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  // Refresh
  ret = 0;
  f = 0;
  refreshMatr(&m1);
  refreshMatr(&m1);
  s21_remove_matrix(&c);
  s21_remove_matrix(&r);

  // 2
  s21_create_matrix(3, 3, &c);

  m4.matrix[0][0] = 1.0;
  m4.matrix[1][0] = 2.0;
  m4.matrix[2][0] = 3.0;

  m5.matrix[0][0] = 3.0;
  m5.matrix[0][1] = 2.0;
  m5.matrix[0][2] = 1.0;

  c.matrix[0][0] = 3.0;
  c.matrix[0][1] = 2.0;
  c.matrix[0][2] = 1.0;
  c.matrix[1][0] = 6.0;
  c.matrix[1][1] = 4.0;
  c.matrix[1][2] = 2.0;
  c.matrix[2][0] = 9.0;
  c.matrix[2][1] = 6.0;
  c.matrix[2][2] = 3.0;

  ret = s21_mult_matrix(&m4, &m5, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  ret = 0;
  f = 0;
  refreshMatr(&m4);
  refreshMatr(&m5);
  refreshMatr(&c);

  // 3
  ret = s21_mult_matrix(&m3, &m4, &r);
  ck_assert_int_eq(1, ret);

  ret = 0;

  // 4
  ret = s21_mult_matrix(&m1, &m5, &r);
  ck_assert_int_eq(2, ret);

  ret = 0;

  // 5
  m6.matrix[0][0] = 2.0;
  c1.matrix[0][0] = 4.0;
  ret = s21_mult_matrix(&m6, &m6, &r);
  f = s21_eq_matrix(&r, &c1);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(trans) {
  // Alloc
  s21_create_matrix(3, 2, &m1);
  s21_create_matrix(1, 1, &m2);
  s21_create_matrix(-100, 0, &m3);
  s21_create_matrix(1, 2, &m4);
  s21_create_matrix(1, 1, &m5);
  s21_create_matrix(1, 1, &m6);
  s21_create_matrix(2, 3, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  m1.matrix[0][0] = 1.0;
  m1.matrix[0][1] = 4.0;
  m1.matrix[1][0] = 2.0;
  m1.matrix[1][1] = 5.0;
  m1.matrix[2][0] = 3.0;
  m1.matrix[2][1] = 6.0;

  c.matrix[0][0] = 1.0;
  c.matrix[0][1] = 2.0;
  c.matrix[0][2] = 3.0;
  c.matrix[1][0] = 4.0;
  c.matrix[1][1] = 5.0;
  c.matrix[1][2] = 6.0;

  // Calc
  ret = s21_transpose(&m1, &r);
  f = s21_eq_matrix(&r, &c);
  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  // Refresh
  ret = 0;
  f = 0;
  refreshMatr(&m1);
  refreshMatr(&c);
  s21_remove_matrix(&r);

  // 2
  ret = s21_transpose(&m3, &r);
  ck_assert_int_eq(1, ret);

  // 3
  m2.matrix[0][0] = 100.0;
  c1.matrix[0][0] = 100.0;

  ret = s21_transpose(&m2, &r);
  f = s21_eq_matrix(&r, &c1);

  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  ret = 0;
  f = 0;

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(calccompl) {
  // Alloc
  s21_create_matrix(5, 5, &m1);
  s21_create_matrix(3, 3, &m2);
  s21_create_matrix(-100, 0, &m3);
  s21_create_matrix(4, 4, &m4);
  s21_create_matrix(1, 1, &m5);
  s21_create_matrix(1, 2, &m6);
  s21_create_matrix(3, 3, &c);
  s21_create_matrix(3, 3, &c1);

  // 1
  m2.matrix[0][0] = 1.0;
  m2.matrix[0][1] = 2.0;
  m2.matrix[0][2] = 3.0;

  m2.matrix[1][0] = 0.0;
  m2.matrix[1][1] = 4.0;
  m2.matrix[1][2] = 2.0;

  m2.matrix[2][0] = 5.0;
  m2.matrix[2][1] = 2.0;
  m2.matrix[2][2] = 1.0;

  c1.matrix[0][0] = 0.0;
  c1.matrix[0][1] = 10.0;
  c1.matrix[0][2] = -20.0;

  c1.matrix[1][0] = 4.0;
  c1.matrix[1][1] = -14.0;
  c1.matrix[1][2] = 8.0;

  c1.matrix[2][0] = -8.0;
  c1.matrix[2][1] = -2.0;
  c1.matrix[2][2] = 4.0;

  ret = s21_calc_complements(&m2, &check);
  f = s21_eq_matrix(&check, &c1);

  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  ret = 0;
  f = 0;
  s21_remove_matrix(&check);
  refreshMatr(&m2);
  refreshMatr(&c1);

  // 2
  m2.matrix[0][0] = -1.0;
  m2.matrix[0][1] = -2.0;
  m2.matrix[0][2] = 2.0;

  m2.matrix[1][0] = 2.0;
  m2.matrix[1][1] = 1.0;
  m2.matrix[1][2] = 1.0;

  m2.matrix[2][0] = 3.0;
  m2.matrix[2][1] = 4.0;
  m2.matrix[2][2] = 5.0;

  c1.matrix[0][0] = 1.0;
  c1.matrix[0][1] = -7.0;
  c1.matrix[0][2] = 5.0;

  c1.matrix[1][0] = 18.0;
  c1.matrix[1][1] = -11.0;
  c1.matrix[1][2] = -2.0;

  c1.matrix[2][0] = -4.0;
  c1.matrix[2][1] = 5.0;
  c1.matrix[2][2] = 3.0;

  ret = s21_calc_complements(&m2, &check);
  f = s21_eq_matrix(&check, &c1);

  ck_assert_int_eq(1, f);
  ck_assert_int_eq(0, ret);

  ret = 0;
  f = 0;
  s21_remove_matrix(&check);
  refreshMatr(&m2);
  refreshMatr(&c1);

  // 3
  ret = s21_calc_complements(&m3, &check);
  ck_assert_int_eq(1, ret);

  ret = 0;
  f = 0;

  // 4
  m6.matrix[0][0] = 1.0;
  m6.matrix[0][1] = 2.0;

  ret = s21_calc_complements(&m6, &check);
  ck_assert_int_eq(2, ret);

  ret = 0;
  f = 0;

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(determinant) {
  // Alloc
  s21_create_matrix(5, 5, &m1);
  s21_create_matrix(3, 3, &m2);
  s21_create_matrix(-100, 0, &m3);
  s21_create_matrix(4, 4, &m4);
  s21_create_matrix(1, 1, &m5);
  s21_create_matrix(2, 3, &m6);
  s21_create_matrix(2, 2, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  m1.matrix[0][0] = 1.0;
  m1.matrix[0][1] = 1.0;
  m1.matrix[0][2] = 1.0;
  m1.matrix[0][3] = 1.0;
  m1.matrix[0][4] = 1.0;

  m1.matrix[1][0] = 1.0;
  m1.matrix[1][1] = 2.0;
  m1.matrix[1][2] = 2.0;
  m1.matrix[1][3] = 2.0;
  m1.matrix[1][4] = 2.0;

  m1.matrix[2][0] = 1.0;
  m1.matrix[2][1] = 2.0;
  m1.matrix[2][2] = 3.0;
  m1.matrix[2][3] = 3.0;
  m1.matrix[2][4] = 3.0;

  m1.matrix[3][0] = 1.0;
  m1.matrix[3][1] = 2.0;
  m1.matrix[3][2] = 3.0;
  m1.matrix[3][3] = 4.0;
  m1.matrix[3][4] = 4.0;

  m1.matrix[4][0] = 1.0;
  m1.matrix[4][1] = 2.0;
  m1.matrix[4][2] = 3.0;
  m1.matrix[4][3] = 4.0;
  m1.matrix[4][4] = 5.0;

  ret = s21_determinant(&m1, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(1.0, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m1);

  // 2
  m2.matrix[0][0] = 0.0;
  m2.matrix[0][1] = 1.0;
  m2.matrix[0][2] = 2.0;

  m2.matrix[1][0] = 0.0;
  m2.matrix[1][1] = 3.0;
  m2.matrix[1][2] = 4.0;

  m2.matrix[2][0] = 0.0;
  m2.matrix[2][1] = 8.0;
  m2.matrix[2][2] = 9.0;

  ret = s21_determinant(&m2, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(0.0, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m2);

  // 3
  m4.matrix[0][0] = 1.0;
  m4.matrix[0][1] = 3.0;
  m4.matrix[0][2] = 4.0;
  m4.matrix[0][3] = 5.0;

  m4.matrix[1][0] = 9.0;
  m4.matrix[1][1] = 8.0;
  m4.matrix[1][2] = 6.0;
  m4.matrix[1][3] = 3.0;

  m4.matrix[2][0] = 1.0;
  m4.matrix[2][1] = 4.0;
  m4.matrix[2][2] = 5.0;
  m4.matrix[2][3] = 1.0;

  m4.matrix[3][0] = 1.0;
  m4.matrix[3][1] = 8.0;
  m4.matrix[3][2] = 7.0;
  m4.matrix[3][3] = 3.0;

  ret = s21_determinant(&m4, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(434.0, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m4);

  // 3
  m4.matrix[0][0] = 0.0;
  m4.matrix[0][1] = 3.0;
  m4.matrix[0][2] = 4.0;
  m4.matrix[0][3] = 5.0;

  m4.matrix[1][0] = 9.0;
  m4.matrix[1][1] = 8.0;
  m4.matrix[1][2] = 6.0;
  m4.matrix[1][3] = 3.0;

  m4.matrix[2][0] = 0.0;
  m4.matrix[2][1] = 4.0;
  m4.matrix[2][2] = 5.0;
  m4.matrix[2][3] = 1.0;

  m4.matrix[3][0] = 1.0;
  m4.matrix[3][1] = 8.0;
  m4.matrix[3][2] = 7.0;
  m4.matrix[3][3] = 3.0;

  ret = s21_determinant(&m4, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(399.0, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m4);

  // 4
  m1.matrix[0][0] = 1.0;
  m1.matrix[0][1] = 4.0;
  m1.matrix[0][2] = 6.0;
  m1.matrix[0][3] = 12.0;
  m1.matrix[0][4] = 15.0;

  m1.matrix[1][0] = -14.0;
  m1.matrix[1][1] = 24.0;
  m1.matrix[1][2] = 3.0;
  m1.matrix[1][3] = 8.0;
  m1.matrix[1][4] = 6.0;

  m1.matrix[2][0] = 9.0;
  m1.matrix[2][1] = 12.0;
  m1.matrix[2][2] = 6.0;
  m1.matrix[2][3] = 9.0;
  m1.matrix[2][4] = 60.0;

  m1.matrix[3][0] = 3.0;
  m1.matrix[3][1] = 4.0;
  m1.matrix[3][2] = 8.0;
  m1.matrix[3][3] = 1.0;
  m1.matrix[3][4] = 4.0;

  m1.matrix[4][0] = 0.0;
  m1.matrix[4][1] = 1.0;
  m1.matrix[4][2] = 2.0;
  m1.matrix[4][3] = 5.0;
  m1.matrix[4][4] = 6.0;

  ret = s21_determinant(&m1, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(45018.0, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m1);

  // 5
  /*
  m2.matrix[0][0] = 3.1;
  m2.matrix[0][1] = 25.8;
  m2.matrix[0][2] = 1.4;

  m2.matrix[1][0] = 2.1;
  m2.matrix[1][1] = 0.0;
  m2.matrix[1][2] = 10.05;

  m2.matrix[2][0] = -8.5;
  m2.matrix[2][1] = 9.76;
  m2.matrix[2][2] = 15.124;

  ret = s21_determinant(&m2, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(-3298.76, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m2);
*/
  // 6
  m5.matrix[0][0] = 123;

  ret = s21_determinant(&m5, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(123, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m5);

  // 7
  c.matrix[0][0] = 1;
  c.matrix[0][1] = 4;

  c.matrix[1][0] = 1000;
  c.matrix[1][1] = -123;

  ret = s21_determinant(&c, &result);

  ck_assert_int_eq(0, ret);
  ck_assert_double_eq(-4123, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&c);

  // 8
  m6.matrix[0][0] = 1;
  m6.matrix[0][1] = 2;
  m6.matrix[0][2] = 4;

  m6.matrix[1][0] = 1;
  m6.matrix[1][1] = 6;
  m6.matrix[1][2] = 1239;

  ret = s21_determinant(&m6, &result);

  ck_assert_int_eq(2, ret);
  ck_assert_double_eq(0.0, result);

  ret = 0;
  result = 0.0;
  refreshMatr(&m6);

  // 9
  ret = s21_determinant(&m3, &result);

  ck_assert_int_eq(1, ret);
  ck_assert_double_eq(0.0, result);

  ret = 0;
  result = 0.0;

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

START_TEST(inverse) {
  // Alloc
  s21_create_matrix(3, 3, &m1);
  s21_create_matrix(-3, -30, &m2);
  s21_create_matrix(15, -3, &m3);
  s21_create_matrix(3, 1, &m4);
  s21_create_matrix(1, 3, &m5);
  s21_create_matrix(1, 1, &m6);
  s21_create_matrix(3, 3, &c);
  s21_create_matrix(1, 1, &c1);

  // 1
  m1.matrix[0][0] = 2.0;
  m1.matrix[0][1] = 5.0;
  m1.matrix[0][2] = 7.0;

  m1.matrix[1][0] = 6.0;
  m1.matrix[1][1] = 3.0;
  m1.matrix[1][2] = 4.0;

  m1.matrix[2][0] = 5.0;
  m1.matrix[2][1] = -2.0;
  m1.matrix[2][2] = -3.0;

  c.matrix[0][0] = 1.0;
  c.matrix[0][1] = -1.0;
  c.matrix[0][2] = 1.0;

  c.matrix[1][0] = -38.0;
  c.matrix[1][1] = 41.0;
  c.matrix[1][2] = -34.0;

  c.matrix[2][0] = 27.0;
  c.matrix[2][1] = -29.0;
  c.matrix[2][2] = 24.0;

  ret = s21_inverse_matrix(&m1, &r);
  f = s21_eq_matrix(&c, &r);

  ck_assert_int_eq(0, ret);
  ck_assert_int_eq(1, f);

  ret = 0;
  f = 0;
  refreshMatr(&m1);
  refreshMatr(&c);

  // 2
  ret = s21_inverse_matrix(&m2, &r);
  ck_assert_int_eq(1, ret);
  ret = 0;

  // 3
  ret = s21_inverse_matrix(&m4, &r);
  ck_assert_int_eq(2, ret);
  ret = 0;

  freeMemory(&m1, &m2, &m3, &m4, &m5, &m6, &c, &c1, &r);
}
END_TEST

int main() {
  Suite *s = suite_create("Suite");
  TCase *tc = tcase_create("Test case");
  SRunner *sr = srunner_create(s);

  int output;
  suite_add_tcase(s, tc);
  tcase_add_test(tc, sum);
  tcase_add_test(tc, sub);
  tcase_add_test(tc, mult_num);
  tcase_add_test(tc, mult);
  tcase_add_test(tc, trans);
  tcase_add_test(tc, calccompl);
  tcase_add_test(tc, determinant);
  tcase_add_test(tc, inverse);

  srunner_run_all(sr, CK_VERBOSE);
  output = srunner_ntests_failed(sr);
  srunner_free(sr);

  return output;
}
