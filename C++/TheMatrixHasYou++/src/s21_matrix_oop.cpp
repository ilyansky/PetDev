#include "s21_matrix_oop.h"

// Init / Deinit
S21Matrix::S21Matrix() {
  rows_ = 1;
  cols_ = 1;
  memalloc(matrix_, rows_, cols_);
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (!isCorrectSize(rows, cols)) throw exception();

  rows_ = rows;
  cols_ = cols;

  memalloc(matrix_, rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  memalloc(matrix_, other.rows_, other.cols_);
  copyMatrix(other.matrix_, matrix_, rows_, cols_);
}

S21Matrix::S21Matrix(S21Matrix&& other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  memalloc(matrix_, other.rows_, other.cols_);
  copyMatrix(other.matrix_, matrix_, rows_, cols_);

  memfree(other.matrix_, other.rows_);
  other.rows_ = 0;
  other.cols_ = 0;
}

S21Matrix::~S21Matrix() { memfree(matrix_, rows_); }

// Sup functions
void S21Matrix::memalloc(double**& m, int rows, int cols) {
  m = new double*[rows];
  for (int i = 0; i < rows; i++) {
    m[i] = new double[cols];

    for (int j = 0; j < cols; j++) {
      m[i][j] = 0.0;
    }
  }
}

void S21Matrix::memfree(double**& m, int rows) {
  for (int i = 0; i < rows; i++) {
    delete[] m[i];
  }
  delete[] m;
}

void S21Matrix::copyMatrix(double** from, double** to, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      to[i][j] = from[i][j];
    }
  }
}

bool S21Matrix::isCorrectSize(int rows, int cols) {
  if (rows < 1 || cols < 1) return false;
  return true;
}

void S21Matrix::printMatrix(S21Matrix m) {
  for (int i = 0; i < m.rows_; i++) {
    for (int j = 0; j < m.cols_; j++) {
      cout << m.matrix_[i][j] << "\t";
    }
    cout << endl;
  }
}

bool S21Matrix::isEqualSizes(int rows1, int rows2, int cols1, int cols2) {
  if (rows1 != rows2 || cols1 != cols2) return false;

  return true;
}

bool S21Matrix::isSquareMatrix(int rows, int cols) {
  if (rows != cols) return false;
  return true;
}

int S21Matrix::swapRows(S21Matrix* m, int startRow, int startCol,
                        double* sign) {
  int flag = 0;

  // Make first row with no zero at [0][0]
  int row = -1;
  for (int i = startRow; i < m->getRows(); i++) {
    if (m->getMatrix()[i][startCol] != 0) {
      row = i;
      break;
    }
  }

  // First col == 0
  if (row == -1) {
    flag = 1;
  } else if (row != startRow) {  // Not zero not at [0][0] -> swap
    double temp = 0.0;

    for (int j = 0; j < m->getCols(); j++) {
      temp = m->getMatrix()[row][j];
      m->getMatrix()[row][j] = m->getMatrix()[startRow][j];
      m->getMatrix()[startRow][j] = temp;
    }
    *sign *= -1.0;
  }

  return flag;
}

void S21Matrix::refreshMatrix(S21Matrix* m) {
  for (int i = 0; i < m->getRows(); i++) {
    for (int j = 0; j < m->getCols(); j++) {
      m->getMatrix()[i][j] = 0.0;
    }
  }
}

// Mutators
void S21Matrix::setRows(int rows) {
  if (rows < 1) throw exception();

  double** temp;
  memalloc(temp, rows, cols_);

  if (rows < rows_) {
    copyMatrix(matrix_, temp, rows, cols_);
  } else {
    copyMatrix(matrix_, temp, rows_, cols_);
  }

  memfree(matrix_, rows_);

  rows_ = rows;
  memalloc(matrix_, rows_, cols_);
  copyMatrix(temp, matrix_, rows_, cols_);

  memfree(temp, rows_);
}

void S21Matrix::setCols(int cols) {
  if (cols < 1) throw exception();

  double** temp;
  memalloc(temp, rows_, cols);

  if (cols < cols_) {
    copyMatrix(matrix_, temp, rows_, cols);
  } else {
    copyMatrix(matrix_, temp, rows_, cols_);
  }

  memfree(matrix_, rows_);

  cols_ = cols;
  memalloc(matrix_, rows_, cols_);
  copyMatrix(temp, matrix_, rows_, cols_);

  memfree(temp, rows_);
}

// Accessors
int S21Matrix::getRows() { return rows_; }

int S21Matrix::getCols() { return cols_; }

double** S21Matrix::getMatrix() { return matrix_; }

// Matrix operations
bool S21Matrix::EqMatrix(const S21Matrix& other) {
  if (!isEqualSizes(rows_, other.rows_, cols_, other.cols_)) return false;

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 0.00000009) return false;
    }
  }

  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (!isEqualSizes(rows_, other.rows_, cols_, other.cols_)) throw exception();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (!isEqualSizes(rows_, other.rows_, cols_, other.cols_)) throw exception();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) throw exception();

  double** tempRes;
  memalloc(tempRes, rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        tempRes[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  memfree(matrix_, rows_);
  memalloc(matrix_, rows_, other.cols_);
  cols_ = other.cols_;
  copyMatrix(tempRes, matrix_, rows_, other.cols_);
  memfree(tempRes, rows_);
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix m(cols_, rows_);

  for (int i = 0; i < cols_; i++) {
    for (int j = 0; j < rows_; j++) {
      m.matrix_[i][j] = matrix_[j][i];
    }
  }

  return m;
}

S21Matrix S21Matrix::CalcComplements() {
  if (!isSquareMatrix(rows_, cols_)) throw exception();

  double det = 0.0;
  double minorValues[(rows_ - 1) * (cols_ - 1)];
  int ind = 0;

  S21Matrix temp(rows_, cols_);
  S21Matrix tempMinor(rows_ - 1, cols_ - 1);

  // Minors matrix
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      // push minors in array
      for (int ii = 0; ii < rows_; ii++) {
        for (int jj = 0; jj < cols_; jj++) {
          if (ii != i && jj != j) {
            minorValues[ind] = matrix_[ii][jj];
            ind++;
          }
        }
      }
      ind = 0;

      // find minors values
      for (int ii = 0; ii < rows_ - 1; ii++) {
        for (int jj = 0; jj < cols_ - 1; jj++) {
          tempMinor.matrix_[ii][jj] = minorValues[ind];
          ind++;
        }
      }
      det = tempMinor.Determinant();
      temp.matrix_[i][j] = det;

      refreshMatrix(&tempMinor);
      ind = 0;
    }
  }

  // Calc complements matrix
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      temp.matrix_[i][j] *= pow(-1, i + j);
    }
  }

  S21Matrix result(rows_, cols_);
  copyMatrix(temp.matrix_, result.matrix_, rows_, cols_);

  return result;
}

double S21Matrix::Determinant() {
  if (!isSquareMatrix(rows_, cols_)) throw exception();
  int ret = 0;
  double div = 1.0;
  double sign = 1.0;

  double upMult = 0.0;
  double bottomMult = 0.0;
  double upJ = 0.0;
  double bottomJ = 0.0;

  double det = 1.0;

  // Init temp matrix
  S21Matrix temp(rows_, cols_);
  copyMatrix(matrix_, temp.matrix_, rows_, cols_);

  ret = swapRows(&temp, 0, 0, &sign);

  if (ret == 1) {
    det = 0.0;
    return det;
  }

  for (int x = 0; x < temp.cols_ - 1; x++) {
    for (int i = x + 1; i < temp.rows_; i++) {
      ret = swapRows(&temp, x, x, &sign);
      if (ret == 1) {
        break;
      }

      if (temp.matrix_[i][x] != 0.0) {
        upMult = temp.matrix_[x][x];
        bottomMult = temp.matrix_[i][x];
        div *= upMult;
        for (int j = 0; j < temp.cols_; j++) {
          upJ = temp.matrix_[x][j];
          bottomJ = temp.matrix_[i][j];
          temp.matrix_[i][j] = upJ * (-bottomMult) + bottomJ * upMult;
        }
      }
    }

    if (ret == 1) {
      ret = 0.0;
      continue;
    }
  }

  // Calc the det
  for (int i = 0; i < temp.rows_; i++) {
    for (int j = 0; j < temp.cols_; j++) {
      if (i == j) {
        det *= temp.matrix_[i][j];
      }
    }
  }

  det *= sign;
  det /= div;

  return det;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = 0.000000;
  det = this->Determinant();

  if (!isSquareMatrix(rows_, cols_) || (det > -0.0000001 && det < 0.0000001))
    throw exception();

  S21Matrix temp1(rows_, cols_);
  copyMatrix(this->matrix_, temp1.matrix_, rows_, cols_);

  S21Matrix temp2 = temp1.CalcComplements();

  S21Matrix temp3 = temp2.Transpose();

  temp3.MulNumber(1 / det);
  return temp3;
}

// Overload operators
S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  if (!isEqualSizes(rows_, other.rows_, cols_, other.cols_)) throw exception();

  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] + other.matrix_[i][j];
    }
  }

  return res;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  if (!isEqualSizes(rows_, other.rows_, cols_, other.cols_)) throw exception();

  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] - other.matrix_[i][j];
    }
  }

  return res;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] = matrix_[i][j] * num;
    }
  }

  return res;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  if (cols_ != other.rows_) throw exception();

  S21Matrix res(rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }

  return res;
}

bool S21Matrix::operator==(const S21Matrix& other) {
  return this->EqMatrix(other);
}

void S21Matrix::operator=(const S21Matrix& other) {
  if (!isEqualSizes(rows_, other.rows_, cols_, other.cols_))
    throw exception();  // checkme

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

void S21Matrix::operator+=(const S21Matrix& other) { this->SumMatrix(other); }

void S21Matrix::operator-=(const S21Matrix& other) { this->SubMatrix(other); }

void S21Matrix::operator*=(const double num) { this->MulNumber(num); }

void S21Matrix::operator*=(const S21Matrix& other) { this->MulMatrix(other); }

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }

  return matrix_[row][col];
}

void S21Matrix::operator()(int row, int col, double val) {
  if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }

  matrix_[row][col] = val;
}
