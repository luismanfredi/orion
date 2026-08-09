#pragma once

#include <initializer_list>
#include <iomanip>
#include <ostream>
#include <vector>

#include "exceptions/MatrixExceptions.hpp"

namespace orion {
class Matrix {
 private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<double> data_;

  std::size_t index(std::size_t row, std::size_t col) const;

 public:
  Matrix(std::size_t r, std::size_t c, double initial_value = 0.0);
  Matrix(std::initializer_list<std::initializer_list<double>> values);

  void fill(double value = 0.0);
  void fillRange(double start, double step = 1.0);

  std::size_t rows() const;
  std::size_t cols() const;

  Matrix operator+(const Matrix& other) const;
  Matrix operator-(const Matrix& other) const;
  Matrix operator*(const Matrix& other) const;
  Matrix operator*(double scalar) const;

  double& operator()(std::size_t r, std::size_t c);
  double operator()(std::size_t r, std::size_t c) const;
  bool operator==(const Matrix& other) const;

  static Matrix zeros(std::size_t r, std::size_t c);
  static Matrix ones(std::size_t r, std::size_t c);

  Matrix transpose() const;

  friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

Matrix operator*(double scalar, const Matrix& matrix);
}  // namespace orion