#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int flag = 0;
  result->rows = rows;
  result->columns = columns;

  flag = isIncorrectMatrix(rows, columns);

  if (flag == 0) {
    // Memory alloc
    result->matrix =
        malloc(rows * columns * sizeof(double) + rows * sizeof(double *));
    double *ptr = (double *)(result->matrix + rows);

    for (int i = 0; i < rows; i++) {
      result->matrix[i] = ptr + columns * i;
    }

    // Init values
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0;
      }
    }
  }

  return flag;  // 0 || 1
}

void s21_remove_matrix(matrix_t *A) { free(A->matrix); }

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = SUCCESS;

  // Sizes of matrixes is eq
  if (isEqualSizes(A, B) && isIncorrectMatrix(A->rows, A->columns) == 0 &&
      isIncorrectMatrix(B->rows, B->columns) == 0) {
    for (int i = 0; i < A->rows && flag == SUCCESS; i++) {
      for (int j = 0; j < A->columns && flag == SUCCESS; j++) {
        // First wrong element -> break both loops
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.00000009)
          flag = FAILURE;
      }
    }
    // Sizes of matrixes isnt eq or incorrect sizes
  } else {
    flag = FAILURE;
  }

  return flag;  // 1 - SUC || 0 - FAIL
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;

  // All checks
  if (isIncorrectMatrix(A->rows, A->columns) ||
      isIncorrectMatrix(B->rows, B->columns)) {
    flag = 1;
  } else if (isEqualSizes(A, B) == 0) {
    flag = 2;
  }

  if (flag == 0) {
    // Init result
    s21_create_matrix(A->rows, A->columns, result);
    // was init result matr? i need know size matrix checkme

    // Sum
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;

  // All checks
  if (isIncorrectMatrix(A->rows, A->columns) ||
      isIncorrectMatrix(B->rows, B->columns)) {
    flag = 1;
  } else if (isEqualSizes(A, B) == 0) {
    flag = 2;
  }

  if (flag == 0) {
    // Init result
    s21_create_matrix(A->rows, A->columns, result);
    // was init result matr? i need know matrix size before init checkme

    // Sub
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }

  return flag;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int flag = 0;

  if (isIncorrectMatrix(A->rows, A->columns)) {
    flag = 1;
  }

  if (flag == 0) {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }

  return flag;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int flag = 0;

  // Check correct
  if (isIncorrectMatrix(A->rows, A->columns) ||
      isIncorrectMatrix(B->rows, B->columns)) {
    flag = 1;
  } else if (A->columns != B->rows) {
    flag = 2;
  }

  if (flag == 0) {
    s21_create_matrix(A->rows, B->columns, result);

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }

  return flag;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int flag = 0;

  if (isIncorrectMatrix(A->rows, A->columns)) {
    flag = 1;
  }

  if (flag == 0) {
    s21_create_matrix(A->columns, A->rows, result);

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }

  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  double det = 0.0;
  double minorValues[(A->rows - 1) * (A->columns - 1)];  // ?
  int ind = 0;
  matrix_t temp;
  matrix_t tempMinor;

  if (isIncorrectMatrix(A->rows, A->columns)) {
    flag = 1;
  } else if (A->rows != A->columns) {
    flag = 2;
  }

  if (flag == 0) {
    s21_create_matrix(A->rows, A->columns, &temp);
    s21_create_matrix(A->rows - 1, A->columns - 1, &tempMinor);

    // Minors matrix
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        // push minors in array
        for (int ii = 0; ii < A->rows; ii++) {
          for (int jj = 0; jj < A->columns; jj++) {
            if (ii != i && jj != j) {
              minorValues[ind] = A->matrix[ii][jj];
              ind++;
            }
          }
        }
        ind = 0;

        // find minors values
        for (int ii = 0; ii < A->rows - 1; ii++) {
          for (int jj = 0; jj < A->columns - 1; jj++) {
            tempMinor.matrix[ii][jj] = minorValues[ind];
            ind++;
          }
        }
        s21_determinant(&tempMinor, &det);
        temp.matrix[i][j] = det;

        refreshMatr(&tempMinor);
        ind = 0;
      }
    }

    // Calc complements matrix
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        temp.matrix[i][j] *= pow(-1, i + j);
      }
    }

    s21_create_matrix(A->rows, A->columns, result);
    eqMatrixes(&temp, result);

    s21_remove_matrix(&temp);
    s21_remove_matrix(&tempMinor);
  }

  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int flag = 0;
  int ret = 0;
  matrix_t tempPrev;
  double div = 1.0;
  double sign = 1.0;

  double upMult = 0.0;
  double bottomMult = 0.0;
  double upJ = 0.0;
  double bottomJ = 0.0;

  double det = 1.0;

  // Check correct
  if (isIncorrectMatrix(A->rows, A->columns)) {
    flag = 1;
  } else if (A->rows != A->columns) {
    flag = 2;
  }

  // Triangle matrix
  if (flag == 0) {
    // Init previous matrix
    s21_create_matrix(A->rows, A->columns, &tempPrev);
    eqMatrixes(A, &tempPrev);

    ret = swapRows(&tempPrev, 0, 0, &sign);
    if (ret == 1) {
      *result = 0.0;
      return flag;
    }

    for (int x = 0; x < tempPrev.columns - 1; x++) {
      for (int i = x + 1; i < tempPrev.rows; i++) {
        ret = swapRows(&tempPrev, x, x, &sign);
        if (ret == 1) {
          break;
        }

        if (tempPrev.matrix[i][x] != 0.0) {    // +
          upMult = tempPrev.matrix[x][x];      // +
          bottomMult = tempPrev.matrix[i][x];  // +
          div *= upMult;
          for (int j = 0; j < tempPrev.columns; j++) {
            upJ = tempPrev.matrix[x][j];
            bottomJ = tempPrev.matrix[i][j];
            tempPrev.matrix[i][j] = upJ * (-bottomMult) + bottomJ * upMult;
          }
        }
      }

      if (ret == 1) {
        ret = 0.0;
        continue;
      }
    }

    // Calc the det
    for (int i = 0; i < tempPrev.rows; i++) {
      for (int j = 0; j < tempPrev.columns; j++) {
        if (i == j) {
          det *= tempPrev.matrix[i][j];
        }
      }
    }

    det *= sign;
    det /= div;
    *result = det;

    s21_remove_matrix(&tempPrev);
  }

  return flag;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  double det = 0.000000;
  s21_determinant(A, &det);

  if (isIncorrectMatrix(A->rows, A->columns)) {
    flag = 1;
  } else if (A->rows != A->columns || (det > -0.0000001 && det < 0.0000001)) {
    flag = 2;
  }

  if (flag == 0) {
    matrix_t temp1;
    matrix_t temp2;
    s21_create_matrix(A->rows, A->columns, &temp1);
    eqMatrixes(A, &temp1);

    s21_calc_complements(&temp1, &temp2);
    s21_remove_matrix(&temp1);

    s21_transpose(&temp2, &temp1);
    s21_remove_matrix(&temp2);

    s21_mult_number(&temp1, 1 / det, result);

    s21_remove_matrix(&temp1);
  }

  return flag;
}