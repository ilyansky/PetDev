#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <math.h>

#include <exception>
#include <iostream>

#include "gtest/gtest.h"

using namespace std;

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;
  double** matrix_;  // Pointer to the memory where the matrix is allocated

  // Sup functions
  void memalloc(double**& m, int rows, int cols);
  void memfree(double**& m, int rows);
  void copyMatrix(double** from, double** to, int rows, int cols);
  void initVals(double** m, int rows, int cols);
  bool isEqualSizes(int rows1, int rows2, int cols1, int cols2);
  bool isCorrectSize(int rows, int cols);
  bool isSquareMatrix(int rows, int cols);
  int swapRows(S21Matrix* m, int startRow, int startCol, double* sign);
  void refreshMatrix(S21Matrix* m);

 public:
  void printMatrix(S21Matrix m);

  // Init / Deinit
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);
  ~S21Matrix();

  // Mutators
  void setRows(int rows);
  void setCols(int cols);

  // Accessors
  int getRows();
  int getCols();
  double** getMatrix();

  // Matrix operations
  bool EqMatrix(const S21Matrix& other);
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();

  // Overload operators
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  void operator=(const S21Matrix& other);
  void operator+=(const S21Matrix& other);
  void operator-=(const S21Matrix& other);
  void operator*=(const double num);
  void operator*=(const S21Matrix& other);
  double& operator()(int row, int col);
  void operator()(int row, int col, double val);
};

#endif
