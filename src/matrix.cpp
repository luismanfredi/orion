#include "orion/matrix.hpp"

#include <algorithm>
#include <iomanip>
#include <string>

#include "orion/math/comparison.hpp"

namespace orion {
Matrix::Matrix(std::size_t r, std::size_t c, double initial_value)
    : rows_(r), cols_(c), data_(r * c, initial_value) {}

Matrix::Matrix(std::initializer_list<std::initializer_list<double>> values) {
  rows_ = values.size();
  if (rows_ == 0) {
    cols_ = 0;
    return;
  }
  cols_ = (*values.begin()).size();
  for (const auto& row : values) {
    if (row.size() != cols_) {
      throw InvalidMatrixDimensions("Invalid Matrix dimensions!");
    }
  }
  data_.reserve(rows_ * cols_);
  for (const auto& row : values) {
    data_.insert(data_.end(), row.begin(), row.end());
  }
}

std::size_t Matrix::index(std::size_t row, std::size_t col) const {
  if (row >= rows_ || col >= cols_) {
    throw PositionNotInMatrix("Position (" + std::to_string(row) + ", " + std::to_string(col) +
                              ") is outside matrix dimensions (" + std::to_string(rows_) + " x " +
                              std::to_string(cols_) + ").");
  }
  return row * cols_ + col;
}

void Matrix::fill(double value) { std::fill(data_.begin(), data_.end(), value); }

void Matrix::fillRange(double start, double step) {
  for (double& element : data_) {
    element = start;
    start += step;
  }
}

std::size_t Matrix::rows() const { return rows_; }

std::size_t Matrix::cols() const { return cols_; }

Matrix Matrix::operator+(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw InvalidMatrixDimensions("Matrix must be same dimensions!");
  }

  Matrix result(rows_, cols_);

  for (std::size_t i = 0; i < data_.size(); ++i) {
    result.data_[i] = data_[i] + other.data_[i];
  }
  return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw InvalidMatrixDimensions("Matrix must be same dimensions!");
  }

  Matrix result(rows_, cols_);

  for (std::size_t i = 0; i < data_.size(); ++i) {
    result.data_[i] = data_[i] - other.data_[i];
  }
  return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
  if (cols_ != other.rows_) {
    throw InvalidMatrixDimensions(
        "The number of columns of the first Matrix must be equal the number of rows of the second "
        "Matrix");
  }

  Matrix result(rows_, other.cols_, 0.0);

  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t k = 0; k < cols_; ++k) {
      double r_ik = data_[i * cols_ + k];
      for (std::size_t j = 0; j < other.cols_; ++j) {
        result.data_[i * other.cols_ + j] += r_ik * other.data_[k * other.cols_ + j];
      }
    }
  }
  return result;
}

Matrix Matrix::operator*(double scalar) const {
  Matrix result(rows_, cols_);

  for (std::size_t i = 0; i < data_.size(); ++i) {
    result.data_[i] = data_[i] * scalar;
  }
  return result;
}

Matrix operator*(double scalar, const Matrix& matrix) { return matrix * scalar; }

double& Matrix::operator()(std::size_t r, std::size_t c) { return data_[index(r, c)]; }

double Matrix::operator()(std::size_t r, std::size_t c) const { return data_[index(r, c)]; }

bool Matrix::operator==(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return false;
  }

  for (std::size_t i = 0; i < data_.size(); ++i) {
    if (!orion::nearlyEqual(data_[i], other.data_[i])) {
      return false;
    }
  }
  return true;
}

Matrix Matrix::zeros(std::size_t r, std::size_t c) { return Matrix(r, c); }

Matrix Matrix::ones(std::size_t r, std::size_t c) { return Matrix(r, c, 1.0); }

Matrix Matrix::transpose() const {
  Matrix result(cols_, rows_);

  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      result.data_[j * rows_ + i] = data_[i * cols_ + j];
    }
  }
  return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) {
  for (std::size_t i = 0; i < mat.rows_; ++i) {
    os << "|";

    for (std::size_t j = 0; j < mat.cols_; ++j) {
      os << std::setw(8) << mat(i, j);
    }
    os << " |\n";
  }
  return os;
}

}  // namespace orion