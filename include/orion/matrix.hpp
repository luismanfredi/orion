#pragma once

#include <initializer_list>
#include <iomanip>
#include <ostream>
#include <vector>

#include "exceptions/MatrixExceptions.hpp"

/**
 * @mainpage Orion
 *
 * @section intro Introduction
 *
 * Orion is a modern C++ library for linear algebra.
 *
 * @section features Features
 *
 * - Matrix representation
 * - Matrix arithmetic
 * - Matrix transposition
 * - Matrix generation
 *
 * @section example Basic example
 *
 * @code
 * #include <orion/matrix.hpp>
 *
 * int main() {
 *     orion::Matrix matrix{{1, 2}, {3, 4}};
 * }
 * @endcode
 */

namespace orion {

/**
 * @brief Represents a mathematical matrix
 *
 * The Matrix class stores elements in a contiguous one-dimensional
 * array using row-major order
 */
class Matrix {
 private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<double> data_;

  /**
   * @brief Returns the linear index corresponding to the given row and column.
   *
   * @param row Given row index.
   * @param col Given column index.
   *
   * @returns Linear index of the given row and column.
   *
   * @throws PositionNotInMatrix If the linear index doesn't exists in the matrix.
   */
  std::size_t index(std::size_t row, std::size_t col) const;

 public:
  /**
   * @brief Creates a matrix with the given dimensions and value.
   *
   * All elements are initialized with zero by default.
   *
   * @param r Number of rows of the matrix.
   * @param c Number of columns of the matrix.
   * @param initial_value Initial value to fill the matrix. Default value of 0.0.
   */
  Matrix(std::size_t r, std::size_t c, double initial_value = 0.0);

  /**
   * @brief Creates a matrix with the given nested initializer lists.
   *
   * @param values matrix values arranged by rows.
   *
   * @throws InvalidMatrixDimensions
   */
  Matrix(std::initializer_list<std::initializer_list<double>> values);

  /**
   * @brief Fill the entire matrix with a chosen value.
   *
   * @param value The value that will fill the matrix.
   */
  void fill(double value = 0.0);

  /**
   * @brief Fill the entire matrix with a sequence of numbers.
   *
   * @param start The number that will start the sequence.
   * @param step The step taken for each number. Default value of 1.0.
   */
  void fillRange(double start, double step = 1.0);

  /**
   * @brief Fill the entire matrix with random values.
   *
   * @param min_val The minimum number a chosen value can assume. Defalt value of 0.0.
   * @param max The maximum number a chosen value can assume. Default value of 1.0.
   */
  void fillRandom(double min_val = 0.0, double max_val = 1.0);

  /**
   * @brief Replace the matrix with an identity matrix.
   *
   * The matrix must be a square matrix.
   *
   * @throws InvalidMatrixDimensions If the matrix is not a square matrix.
   */
  void setIdentity();

  /**
   * @brief Fill the entire matrix with Zeros.
   *
   */
  void setZeros();

  /**
   * @brief Fill the entire matrix with Ones.
   */
  void setOnes();

  /**
   * @brief Returns the number of rows of the matrix.
   *
   * @returns Number of rows in matrix.
   */
  std::size_t rows() const;

  /**
   * @brief Returns the number of columns of the matrix.
   *
   * @returns Number of columns in matrix.
   */
  std::size_t cols() const;

  /**
   * @brief Add two Matrices.
   *
   * @param other Matrix to add.
   *
   * @returns The resulting matrix.
   *
   * @throws InvalidMatrixDimensions If the two matrix don't have the same dimensions.
   */
  Matrix operator+(const Matrix& other) const;

  /**
   * @brief Subtract two Matrices.
   *
   * @param other Matrix to subtract.
   *
   * @returns The resulting matrix.
   *
   * @throws InvalidMatrixDimensions If the two matrix don't have the samedimensions.
   */
  Matrix operator-(const Matrix& other) const;

  /**
   * @brief Multiply two Matrices.
   *
   * @param other Matrix to multiply.
   *
   * @returns The resulting matrix.
   *
   * @throws InvalidMatrixDimensions If the number of columns of the first matrix isn't equal to the
   * number of rows of the second matrix.
   */
  Matrix operator*(const Matrix& other) const;

  /**
   * @brief Multiply all the given matrix values by a scalar number.
   *
   * This operator allows matrix * scalar multiply.
   *
   * @param scalar Number that will multiply the matrix.
   *
   * @returns The resulting matrix.
   */
  Matrix operator*(double scalar) const;

  /**
   * @brief Provides access to a matrix element using Matrix(row, column).
   *
   * This operator CAN modify a value. (e. g. A(1, 2) = 4.0).
   *
   * @param r The row you want to access.
   *
   * @returns Element in the chosen position
   */
  double& operator()(std::size_t r, std::size_t c);

  /**
   * @brief Provides access to a matrix element using Matrix(row, column).
   *
   * This operator CANNOT modify a value.
   *
   * @param r The row you want to access.
   * @param c The column you want to access.
   *
   * @returns Element in the chosen position.
   */
  double operator()(std::size_t r, std::size_t c) const;

  /**
   * @brief Compares two matrices for equality.
   *
   * @returns True If the two matrices are the same.
   * @returns False If the two matrices have a difference.
   */
  bool operator==(const Matrix& other) const;

  /**
   * @brief Compares two matrices for inequality.
   *
   * @returns True If the two matrices have a difference.
   * @returns False If the two matrices are the same.
   */
  bool operator!=(const Matrix& other) const;

  /**
   * @brief Returns a zero matrix.
   *
   * @param r Number of rows of the matrix.
   * @param c Number of columns of the Mamatrixtrix.
   *
   * @returns Zero matrix.
   */
  static Matrix zeros(std::size_t r, std::size_t c);

  /**
   * @brief Returns a matrix filled with ones.
   *
   * @param r Number of rows of the matrix.
   * @param c Number of columns of the matrix.
   *
   * @returns A matrix filled with the number one.
   */
  static Matrix ones(std::size_t r, std::size_t c);

  /**
   * @brief Returns an identity matrix.
   *
   * @param size The size of the matrix (identity matrices must be square).
   *
   * @returns Identity matrix.
   */
  static Matrix identity(std::size_t size);

  /**
   * @brief Returns matrix with random numbers.
   *
   * @param r Number of rows of the matrix.
   * @param c Number of columns of the matrix.
   * @param min_val The minimum number a chosen value can assume. Defalt value of 0.0.
   * @param max The maximum number a chosen value can assume. Defalt value of 1.0.
   *
   * @returns A matrix with random values.
   */
  static Matrix random(std::size_t r, std::size_t c, double min_val = 0.0, double max_value = 1.0);

  /**
   * @brief Transposes the matrix.
   *
   * Swaps the matrix's rows and columns.
   *
   * @returns The matrix transposed.
   */
  Matrix transpose() const;

  /**
   * @brief Inserts a matrix into an output stream.
   *
   * e.g. std::cout << MatrixA.
   *
   * @param Matrix The specified matrix.
   */
  friend std::ostream& operator<<(std::ostream&, const Matrix&);
};

/**
 * @brief Multiply all the given matrix values by a scalar number.
 *
 * This operator allows scalar * matrix multiply.
 *
 * @param scalar Number that will multiply the matrix.
 *
 * @returns The resulting matrix.
 */
Matrix operator*(double scalar, const Matrix& matrix);
}  // namespace orion