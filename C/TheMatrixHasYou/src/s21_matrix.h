#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 0.0000001

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);     // +
void s21_remove_matrix(matrix_t *A);                                // +
int s21_eq_matrix(matrix_t *A, matrix_t *B);                        // +
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // +
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // +
int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // +
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    // +
int s21_transpose(matrix_t *A, matrix_t *result);                   // +
int s21_calc_complements(matrix_t *A, matrix_t *result);            // +
int s21_determinant(matrix_t *A, double *result);                   // +
int s21_inverse_matrix(matrix_t *A, matrix_t *result);              // +

// Sup funcs
int isIncorrectMatrix(int rows, int columns);                              // +
int isEqualSizes(matrix_t *A, matrix_t *B);                                // +
void printMatr(matrix_t *matr);                                            // +
void refreshMatr(matrix_t *matr);                                          // +
void eqMatrixes(matrix_t *from, matrix_t *to);                             // +
int swapRows(matrix_t *matrix, int startRow, int startCol, double *sign);  // +

#endif
