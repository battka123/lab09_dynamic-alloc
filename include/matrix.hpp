
#ifndef INCLUDE_MATRIX_HPP_
#define INCLUDE_MATRIX_HPP_

struct Matrix {
  int** data_ = nullptr;
  size_t n_ = 0u;
  size_t m_ = 0u;
};

void Construct(Matrix& out, size_t n, size_t m);
void Destruct(Matrix& in);

Matrix Copy(const Matrix& matrix);
Matrix Add(const Matrix& a, const Matrix& b);
Matrix Sub(const Matrix& a, const Matrix& b);
Matrix Mult(const Matrix& a, const Matrix& b);

void Transposition(Matrix& matrix);

bool operator==(const Matrix& a, const Matrix& b);

#endif  // INCLUDE_MATRIX_HPP_
