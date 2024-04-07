#include "s21_matrix.h"

// 0 - correct, 1 - incorrect
int isIncorrectMatrix(int rows, int columns) {
  int flag = 0;

  if (rows < 1 || columns < 1) flag = 1;

  return flag;
}

int isEqualSizes(matrix_t *A, matrix_t *B) {
  int flag = 0;

  if (A->rows == B->rows && A->columns == B->columns) flag = 1;

  return flag;
}

void refreshMatr(matrix_t *matr) {
  for (int i = 0; i < matr->rows; i++) {
    for (int j = 0; j < matr->columns; j++) {
      matr->matrix[i][j] = 0.0;
    }
  }
}

void printMatr(matrix_t *matr) {
  for (int i = 0; i < matr->rows; i++) {
    for (int j = 0; j < matr->columns; j++) {
      printf("%f ", matr->matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void eqMatrixes(matrix_t *from, matrix_t *to) {
  for (int i = 0; i < from->rows; i++) {
    for (int j = 0; j < from->columns; j++) {
      to->matrix[i][j] = from->matrix[i][j];
    }
  }
}

int swapRows(matrix_t *matrix, int startRow, int startCol, double *sign) {
  int flag = 0;

  // Make first row with no zero at [0][0]
  int row = -1;
  for (int i = startRow; i < matrix->rows; i++) {
    if (matrix->matrix[i][startCol] != 0) {
      row = i;
      break;
    }
  }

  // First col == 0
  if (row == -1) {
    flag = 1;
  } else if (row != startRow) {  // Not zero not at [0][0] -> swap
    double temp = 0.0;

    for (int j = 0; j < matrix->columns; j++) {
      temp = matrix->matrix[row][j];
      matrix->matrix[row][j] = matrix->matrix[startRow][j];
      matrix->matrix[startRow][j] = temp;
    }
    *sign *= -1.0;
  }

  return flag;
}
