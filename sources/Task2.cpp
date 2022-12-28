// Copyright 2022 Ivan Sushin <i.suschin@yamdex.ru>

#include "matrix.hpp"

void Alloc(Matrix& out) {
  out.data_ = (int**)malloc(out.n_ * sizeof(int*));
  for (size_t i = 0; i < out.n_; ++i) {
    out.data_[i] = (int*)malloc(out.m_ * sizeof(int*));
  }
}

void Destruct(Matrix& in) {
  for (size_t i = 0; i < in.n_; i++) {
    free(in.data_[i]);
  }
  in.data_ = nullptr;
  in.n_ = 0;
  in.m_ = 0;
}

void Construct(Matrix& out, size_t n, size_t m) {
  out.n_ = n;  // строки
  out.m_ = m;  // столбцы

  Alloc(out);

  for (size_t i = 0; i < out.n_; ++i) {
    for (size_t j = 0; j < out.m_; ++j) {
      out.data_[i][j] = 0;
    }
  }
}

Matrix Copy(const Matrix& matrix) {
  Matrix copy_matrix;
  copy_matrix.n_ = matrix.n_;
  copy_matrix.m_ = matrix.m_;
  Alloc(copy_matrix);
  for (size_t i = 0; i < matrix.n_; ++i) {
    for (size_t j = 0; j < matrix.m_; ++j) {
      copy_matrix.data_[i][j] = matrix.data_[i][j];
    }
  }
  return copy_matrix;
}
Matrix Add_or_Sub(const Matrix& a, const Matrix& b, int k) {
  Matrix c;
  if (a.n_ == b.n_ && a.m_ == b.m_) {  // Проверка на нужную матрицу
    Construct(c, a.n_, a.m_);  // Создаю нулевую матрицу
    for (size_t i = 0; i < a.m_; ++i) {    // счётчик строк
      for (size_t j = 0; j < a.n_; ++j) {  // счётчик столбцов
        if (k == 1)
          c.data_[i][j] = (a.data_[i][j] + b.data_[i][j]);  // Сумма элементов
        else if (k == 2)
          c.data_[i][j] = (a.data_[i][j] - b.data_[i][j]);  // разность
                                                            // элементов
      }
    }
  } else
    (Destruct(c));
  return c;
}
Matrix Add(const Matrix& a, const Matrix& b) {
  int k = 1;
  return Add_or_Sub(a, b, k);
}
Matrix Sub(const Matrix& a, const Matrix& b) {
  int k = 2;
  return Add_or_Sub(a, b, k);
}
Matrix Mult(const Matrix& a, const Matrix& b) {
  Matrix c;
  if (a.n_ ==
      b.m_) {  // если кол-во столбцов n матрицы a = кол-ву строк m матрицы b
    Construct(c, b.n_,
              a.m_);  // Создаю нулевую матрицу, столбцов как у второй, строк
                      // как у первой то есть n_=[b.n]  на m_=[a.m]
    for (size_t i = 0; i < c.n_; ++i) {  // переюираю столбцов матрицы с
      for (size_t j = 0; j < c.m_; ++j) {  // перебираю строк матрицы с
        for (size_t k = 0; k < a.n_; ++k) {
          c.data_[i][j] += ((b.data_[i][k]) * (a.data_[k][j]));
        }
      }
    }
  } else
    (Destruct(c));
  return c;
}

void Transposition(Matrix& matrix) {
  for (size_t i = 0; i < matrix.n_; i++) {
    for (size_t j = i; j < matrix.m_; j++) {
      int buf = matrix.data_[i][j];
      matrix.data_[i][j] = matrix.data_[j][i];
      matrix.data_[j][i] = buf;
    }
  }
}
bool operator==(const Matrix& a, const Matrix& b) {
  if (a.m_ == b.m_ && a.n_ == b.n_) {
    for (size_t i = 0; i < a.n_; i++)
      for (size_t j = 0; i < a.m_; j++)
        if (a.data_[i][j] == b.data_[i][j]) {
          continue;
        } else
          return a.data_ != b.data_;
  }
  return (a.data_ == b.data_ && a.m_ == b.m_ && a.n_ == b.n_);
}
