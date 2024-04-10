#include "s21_matrix_oop.h"

TEST(setColsRows, test) {
  S21Matrix m(3, 3);
  m.getMatrix()[0][0] = 2.0;
  m.getMatrix()[0][1] = 5.0;
  m.getMatrix()[0][2] = 7.0;

  m.getMatrix()[1][0] = 6.0;
  m.getMatrix()[1][1] = 3.0;
  m.getMatrix()[1][2] = 4.0;

  m.getMatrix()[2][0] = 5.0;
  m.getMatrix()[2][1] = -2.0;
  m.getMatrix()[2][2] = -3.0;

  EXPECT_ANY_THROW(m.setRows(0));
  EXPECT_ANY_THROW(m.setCols(-123));
  EXPECT_ANY_THROW(S21Matrix m1(-4, -4));
  EXPECT_ANY_THROW(S21Matrix m1(-4, 4));
  EXPECT_ANY_THROW(S21Matrix m1(4, -4));
  EXPECT_ANY_THROW(S21Matrix m1(0, 0));

  S21Matrix c(3, 4);
  c.getMatrix()[0][0] = 2.0;
  c.getMatrix()[0][1] = 5.0;
  c.getMatrix()[0][2] = 7.0;
  c.getMatrix()[0][3] = 0.0;

  c.getMatrix()[1][0] = 6.0;
  c.getMatrix()[1][1] = 3.0;
  c.getMatrix()[1][2] = 4.0;
  c.getMatrix()[1][3] = 0.0;

  c.getMatrix()[2][0] = 5.0;
  c.getMatrix()[2][1] = -2.0;
  c.getMatrix()[2][2] = -3.0;
  c.getMatrix()[2][3] = 0.0;

  m.setCols(4);
  EXPECT_EQ(true, m == c);
  m.setCols(3);

  S21Matrix c1(4, 3);
  c1.getMatrix()[0][0] = 2.0;
  c1.getMatrix()[0][1] = 5.0;
  c1.getMatrix()[0][2] = 7.0;

  c1.getMatrix()[1][0] = 6.0;
  c1.getMatrix()[1][1] = 3.0;
  c1.getMatrix()[1][2] = 4.0;

  c1.getMatrix()[2][0] = 5.0;
  c1.getMatrix()[2][1] = -2.0;
  c1.getMatrix()[2][2] = -3.0;

  c1.getMatrix()[3][0] = 0.0;
  c1.getMatrix()[3][1] = 0.0;
  c1.getMatrix()[3][2] = 0.0;

  m.setRows(4);
  EXPECT_EQ(true, m == c1);
  m.setRows(3);
}

TEST(sum, test) {
  S21Matrix m(3, 3);
  m.getMatrix()[0][0] = 2.0;
  m.getMatrix()[0][1] = 5.0;
  m.getMatrix()[0][2] = 7.0;

  m.getMatrix()[1][0] = 6.0;
  m.getMatrix()[1][1] = 3.0;
  m.getMatrix()[1][2] = 4.0;

  m.getMatrix()[2][0] = 5.0;
  m.getMatrix()[2][1] = -2.0;
  m.getMatrix()[2][2] = -3.0;

  S21Matrix c(3, 3);
  c.getMatrix()[0][0] = 4.0;
  c.getMatrix()[0][1] = 10.0;
  c.getMatrix()[0][2] = 14.0;

  c.getMatrix()[1][0] = 12.0;
  c.getMatrix()[1][1] = 6.0;
  c.getMatrix()[1][2] = 8.0;

  c.getMatrix()[2][0] = 10.0;
  c.getMatrix()[2][1] = -4.0;
  c.getMatrix()[2][2] = -6.0;

  m.SumMatrix(m);
  EXPECT_EQ(true, m == c);

  S21Matrix z = m + m;
  EXPECT_EQ(true, z == c + c);
  m += m;
  EXPECT_EQ(true, z == m);

  S21Matrix one(1, 1);
  one(0, 0, 1.3);
  EXPECT_EQ(1.3, one(0, 0));

  S21Matrix c1(3, 4);
  S21Matrix c2(4, 3);
  EXPECT_ANY_THROW(m.SumMatrix(c1));
  EXPECT_ANY_THROW(m.SumMatrix(c2));
  EXPECT_ANY_THROW(m + c1);
  EXPECT_ANY_THROW(m + c2);
  EXPECT_ANY_THROW(m += c2);
}

TEST(sub, test) {
  S21Matrix m(3, 3);
  m.getMatrix()[0][0] = 2.0;
  m.getMatrix()[0][1] = 5.0;
  m.getMatrix()[0][2] = 7.0;

  m.getMatrix()[1][0] = 6.0;
  m.getMatrix()[1][1] = 3.0;
  m.getMatrix()[1][2] = 4.0;

  m.getMatrix()[2][0] = 5.0;
  m.getMatrix()[2][1] = -2.0;
  m.getMatrix()[2][2] = -3.0;

  S21Matrix m1(3, 3);
  m1.getMatrix()[0][0] = 3.0;
  m1.getMatrix()[0][1] = 0.0;
  m1.getMatrix()[0][2] = 0.0;

  m1.getMatrix()[1][0] = 0.0;
  m1.getMatrix()[1][1] = 3.0;
  m1.getMatrix()[1][2] = 0.0;

  m1.getMatrix()[2][0] = 0.0;
  m1.getMatrix()[2][1] = 0.0;
  m1.getMatrix()[2][2] = -2.0;

  S21Matrix c(3, 3);
  c.getMatrix()[0][0] = -1.0;
  c.getMatrix()[0][1] = 5.0;
  c.getMatrix()[0][2] = 7.0;

  c.getMatrix()[1][0] = 6.0;
  c.getMatrix()[1][1] = 0.0;
  c.getMatrix()[1][2] = 4.0;

  c.getMatrix()[2][0] = 5.0;
  c.getMatrix()[2][1] = -2.0;
  c.getMatrix()[2][2] = -1.0;

  m.SubMatrix(m1);
  EXPECT_EQ(true, m == c);

  m.SumMatrix(m1);
  EXPECT_EQ(true, m - m1 == c);

  m -= m1;
  EXPECT_EQ(true, m == c);

  S21Matrix c1(3, 4);
  S21Matrix c2(4, 3);
  EXPECT_ANY_THROW(m.SumMatrix(c1));
  EXPECT_ANY_THROW(m.SumMatrix(c2));
  EXPECT_ANY_THROW(m - c1);
  EXPECT_ANY_THROW(m - c2);
  EXPECT_ANY_THROW(m -= c2);
}

TEST(mulnum, test) {
  S21Matrix m(3, 3);
  m.getMatrix()[0][0] = 2.0;
  m.getMatrix()[0][1] = 5.0;
  m.getMatrix()[0][2] = 7.0;

  m.getMatrix()[1][0] = 6.0;
  m.getMatrix()[1][1] = 3.0;
  m.getMatrix()[1][2] = 4.0;

  m.getMatrix()[2][0] = 5.0;
  m.getMatrix()[2][1] = -2.0;
  m.getMatrix()[2][2] = -3.0;

  S21Matrix c(3, 3);
  c.getMatrix()[0][0] = 4.0;
  c.getMatrix()[0][1] = 10.0;
  c.getMatrix()[0][2] = 14.0;

  c.getMatrix()[1][0] = 12.0;
  c.getMatrix()[1][1] = 6.0;
  c.getMatrix()[1][2] = 8.0;

  c.getMatrix()[2][0] = 10.0;
  c.getMatrix()[2][1] = -4.0;
  c.getMatrix()[2][2] = -6.0;

  m.MulNumber(2);
  EXPECT_EQ(true, m == c);

  m.MulNumber(0.5);
  EXPECT_EQ(true, m * 2 == c);

  m *= 2;
  EXPECT_EQ(true, m == c);
}

TEST(mulnmatr, test) {
  S21Matrix m(3, 2);
  m.getMatrix()[0][0] = 2.0;
  m.getMatrix()[0][1] = 5.0;

  m.getMatrix()[1][0] = 6.0;
  m.getMatrix()[1][1] = 7.0;

  m.getMatrix()[2][0] = 5.0;
  m.getMatrix()[2][1] = 9.0;

  S21Matrix m2(3, 2);
  m2.getMatrix()[0][0] = 2.0;
  m2.getMatrix()[0][1] = 5.0;

  m2.getMatrix()[1][0] = 6.0;
  m2.getMatrix()[1][1] = 7.0;

  m2.getMatrix()[2][0] = 5.0;
  m2.getMatrix()[2][1] = 9.0;

  S21Matrix m1(2, 3);
  m1.getMatrix()[0][0] = 5.0;
  m1.getMatrix()[0][1] = 4.0;
  m1.getMatrix()[0][2] = 6.0;

  m1.getMatrix()[1][0] = 3.0;
  m1.getMatrix()[1][1] = 5.0;
  m1.getMatrix()[1][2] = -2.0;

  S21Matrix c(3, 3);
  c.getMatrix()[0][0] = 25.0;
  c.getMatrix()[0][1] = 33.0;
  c.getMatrix()[0][2] = 2.0;

  c.getMatrix()[1][0] = 51.0;
  c.getMatrix()[1][1] = 59.0;
  c.getMatrix()[1][2] = 22.0;

  c.getMatrix()[2][0] = 52.0;
  c.getMatrix()[2][1] = 65.0;
  c.getMatrix()[2][2] = 12.0;

  m.MulMatrix(m1);

  EXPECT_EQ(true, m == c);
  EXPECT_EQ(true, m2 * m1 == c);
  m2 *= m1;
  EXPECT_EQ(true, m2 == c);

  S21Matrix x1(3, 2);
  S21Matrix x2(3, 2);
  EXPECT_ANY_THROW(x1.MulMatrix(x2));
  EXPECT_ANY_THROW(x1 * x2);
  EXPECT_ANY_THROW(x1 *= x2);
}

TEST(transpose, test) {
  S21Matrix m(3, 2);
  m.getMatrix()[0][0] = 2.0;
  m.getMatrix()[0][1] = 5.0;

  m.getMatrix()[1][0] = 6.0;
  m.getMatrix()[1][1] = 7.0;

  m.getMatrix()[2][0] = 5.0;
  m.getMatrix()[2][1] = 9.0;

  S21Matrix m1(2, 3);
  m1.getMatrix()[0][0] = 2.0;
  m1.getMatrix()[0][1] = 6.0;
  m1.getMatrix()[0][2] = 5.0;

  m1.getMatrix()[1][0] = 5.0;
  m1.getMatrix()[1][1] = 7.0;
  m1.getMatrix()[1][2] = 9.0;

  S21Matrix c = m.Transpose();

  EXPECT_EQ(true, c == m1);
}

TEST(calccompl, test) {
  S21Matrix m2(3, 3);
  m2(0, 0, 1.0);
  m2(0, 1, 2.0);
  m2(0, 2, 3.0);

  m2(1, 0, 0.0);
  m2(1, 1, 4.0);
  m2(1, 2, 2.0);

  m2(2, 0, 5.0);
  m2(2, 1, 2.0);
  m2(2, 2, 1.0);

  S21Matrix c1(3, 3);
  c1(0, 0, 0.0);
  c1(0, 1, 10.0);
  c1(0, 2, -20.0);

  c1(1, 0, 4.0);
  c1(1, 1, -14.0);
  c1(1, 2, 8.0);

  c1(2, 0, -8.0);
  c1(2, 1, -2.0);
  c1(2, 2, 4.0);

  S21Matrix r = m2.CalcComplements();
  EXPECT_EQ(true, r == c1);

  S21Matrix c2(3, 4);
  EXPECT_ANY_THROW(c2.CalcComplements());
}

TEST(det, test) {
  S21Matrix m2(4, 4);
  m2(0, 0, 1.0);
  m2(0, 1, 3.0);
  m2(0, 2, 4.0);
  m2(0, 3, 5.0);

  m2(1, 0, 9.0);
  m2(1, 1, 8.0);
  m2(1, 2, 6.0);
  m2(1, 3, 3.0);

  m2(2, 0, 1.0);
  m2(2, 1, 4.0);
  m2(2, 2, 5.0);
  m2(2, 3, 1.0);

  m2(3, 0, 1.0);
  m2(3, 1, 8.0);
  m2(3, 2, 7.0);
  m2(3, 3, 3.0);

  double det = m2.Determinant();

  EXPECT_EQ(434.0, det);

  S21Matrix c2(3, 4);
  EXPECT_ANY_THROW(c2.CalcComplements());
}

TEST(inv, test) {
  S21Matrix m1(3, 3);
  m1(0, 0, 2.0);
  m1(0, 1, 5.0);
  m1(0, 2, 7.0);

  m1(1, 0, 6.0);
  m1(1, 1, 3.0);
  m1(1, 2, 4.0);

  m1(2, 0, 5.0);
  m1(2, 1, -2.0);
  m1(2, 2, -3.0);

  S21Matrix c1(3, 3);
  c1(0, 0, 1.0);
  c1(0, 1, -1.0);
  c1(0, 2, 1.0);

  c1(1, 0, -38.0);
  c1(1, 1, 41.0);
  c1(1, 2, -34.0);

  c1(2, 0, 27.0);
  c1(2, 1, -29.0);
  c1(2, 2, 24.0);

  S21Matrix c2 = m1.InverseMatrix();
  EXPECT_EQ(true, c1 == c2);

  S21Matrix c3(3, 4);
  EXPECT_ANY_THROW(c3.InverseMatrix());

  S21Matrix x(1, 1);
  x(0, 0, 0);
  EXPECT_ANY_THROW(x.InverseMatrix());
}

TEST(another, test) {
  // =
  S21Matrix m(1, 1);
  S21Matrix m1(1, 1);
  S21Matrix m2(2, 2);
  m1(0, 0, 1.0);
  m = m1;
  EXPECT_EQ(true, m == m1);
  EXPECT_ANY_THROW(m = m2);

  // (i, j)
  EXPECT_ANY_THROW(m(2, 2, 2.0));
  EXPECT_ANY_THROW(m(-1, -2, 123));
  EXPECT_ANY_THROW(m(-3, -4));
}