#include "orion/matrix.hpp"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include "orion/math/comparison.hpp"

namespace orion {
Matrix::Matrix(std::size_t rows, std::size_t cols, double initial_value)
    : rows_(rows), cols_(cols), data_(rows * cols, initial_value) {}

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

Matrix::Matrix(std::vector<std::vector<double>> values) {
  rows_ = values.size();
  if (rows_ == 0) {
    cols_ = 0;
    return;
  }
  cols_ = values[0].size();
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

void Matrix::fillRandom(double min_val, double max_val) {
  static thread_local std::mt19937 gen(std::random_device{}());
  std::uniform_real_distribution<double> dist(min_val, max_val);

  for (auto& element : data_) {
    element = dist(gen);
  }
}

void Matrix::setIdentity() {
  if (rows_ != cols_) {
    throw InvalidMatrixDimensions("Identity Matrices MUST be square (e.g 2x2; 3x3; ...).");
  }

  this->fill(0.0);

  for (std::size_t i = 0; i < rows_; ++i) {
    (*this)(i, i) = 1.0;
  }
}

void Matrix::setZeros() { this->fill(0.0); }

void Matrix::setOnes() { this->fill(1.0); }

std::size_t Matrix::rows() const { return rows_; }

std::size_t Matrix::cols() const { return cols_; }

double Matrix::sum() const {
  double result = 0.0;

  for (double value : data_) {
    result += value;
  }
  return result;
}

Matrix Matrix::sum(int axis) const {
  if (axis == 0) {
    Matrix result(1, cols_);

    for (std::size_t i = 0; i < rows_; ++i) {
      for (std::size_t j = 0; j < cols_; ++j) {
        result(0, j) += (*this)(i, j);
      }
    }
    return result;
  } else if (axis == 1) {
    Matrix result(rows_, 1);

    for (std::size_t i = 0; i < rows_; ++i) {
      for (std::size_t j = 0; j < cols_; ++j) {
        result(i, 0) += (*this)(i, j);
      }
    }
    return result;
  }

  throw InvalidAxis(
      "Invalid Axis value. 0 to sums vertically down the rows, 1 to sums horizontally across the "
      "columns.");
}

double Matrix::mean() const {
  double sum = this->sum();

  double result = sum / static_cast<double>(data_.size());

  return result;
}

double Matrix::max() const { return *std::max_element(data_.begin(), data_.end()); }

Matrix Matrix::max(int axis) const {
  if (axis == 0) {
    Matrix result(1, cols_);

    for (std::size_t j = 0; j < cols_; ++j) {
      result.data_[j] = (*this)(0, j);
    }

    for (std::size_t i = 1; i < rows_; ++i) {
      for (std::size_t j = 0; j < cols_; ++j) {
        result.data_[j] = std::max(result.data_[j], (*this)(i, j));
      }
    }

    return result;
  }

  if (axis == 1) {
    Matrix result(rows_, 1);

    for (std::size_t i = 0; i < rows_; ++i) {
      result.data_[i] = (*this)(i, 0);
    }

    for (std::size_t i = 0; i < rows_; ++i) {
      for (std::size_t j = 1; j < cols_; j++) {
        result.data_[i] = std::max(result.data_[i], (*this)(i, j));
      }
    }

    return result;
  }

  throw InvalidAxis("Error");
}

Matrix Matrix::hadamard(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw InvalidMatrixDimensions("Matrix must be same dimensions!");
  }

  Matrix result(rows_, cols_);

  for (std::size_t i = 0; i < data_.size(); ++i) {
    result.data_[i] = data_[i] * other.data_[i];
  }
  return result;
}

Matrix Matrix::operator+(const Matrix& other) const {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < data_.size(); ++i) {
      result.data_[i] = data_[i] + other.data_[i];
    }
    return result;
  }

  else if (other.rows_ == 1 && cols_ == other.cols_) {
    Matrix result(rows_, cols_);
    for (std::size_t i = 0; i < rows_; ++i) {
      for (std::size_t j = 0; j < cols_; ++j) {
        result.data_[i * cols_ + j] = data_[i * cols_ + j] + other.data_[j];
      }
    }
    return result;
  }

  else {
    throw InvalidMatrixDimensions("Incompatible matrix dimensions!");
  }
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
        "The number of columns of the first Matrix must be equal the number of rows of the "
        "second "
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

Matrix Matrix::operator/(double scalar) const {
  Matrix result(rows_, cols_);

  for (std::size_t i = 0; i < data_.size(); ++i) {
    result.data_[i] = data_[i] / scalar;
  }
  return result;
}

double& Matrix::operator()(std::size_t rows, std::size_t cols) { return data_[index(rows, cols)]; }

double Matrix::operator()(std::size_t rows, std::size_t cols) const {
  return data_[index(rows, cols)];
}

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

bool Matrix::operator!=(const Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    return true;
  }

  for (std::size_t i = 0; i < data_.size(); ++i) {
    if (!orion::nearlyEqual(data_[i], other.data_[i])) {
      return true;
    }
  }
  return false;
}

Matrix Matrix::zeros(std::size_t rows, std::size_t cols) { return {rows, cols}; }

Matrix Matrix::ones(std::size_t rows, std::size_t cols) { return {rows, cols, 1.0}; }

Matrix Matrix::identity(std::size_t size) {
  Matrix result(size, size);

  for (std::size_t i = 0; i < size; ++i) {
    result(i, i) = 1.0;
  }

  return result;
}

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters)
Matrix Matrix::random(std::size_t rows, std::size_t cols, double min_val, double max_value) {
  Matrix result(rows, cols);
  result.fillRandom(min_val, max_value);
  return result;
}

Matrix Matrix::transpose() const {
  Matrix result(cols_, rows_);

  for (std::size_t i = 0; i < rows_; ++i) {
    for (std::size_t j = 0; j < cols_; ++j) {
      result.data_[j * rows_ + i] = data_[i * cols_ + j];
    }
  }

  return result;
}

Matrix Matrix::log() const {
  Matrix result(rows_, cols_);

  std::transform(data_.begin(), data_.end(), result.data_.begin(), [](double x) {
    if (x <= 0) {
      throw std::domain_error("log() requires positives values.");
    }
    return std::log(x);
  });

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