#include "s21_matrix.h"

int main() {

  matrix_t m1;
  matrix_t r;
  s21_create_matrix(3, 2, &m1);
  m1.matrix[0][0] = 1.0;
  m1.matrix[0][1] = 4.0;
  m1.matrix[1][0] = 2.0;
  m1.matrix[1][1] = 5.0;
  m1.matrix[2][0] = 3.0;
  m1.matrix[2][1] = 6.0;

  s21_transpose(&m1, &r);
  printMatr(&r);

  return 0;
}
