#pragma once

#include <initializer_list>
#include <iomanip>
#include <ostream>
#include <vector>

#include "exceptions/MathExceptions.hpp"
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
 * array using row-major order.
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
   * @throws PositionNotInMatrix If the provided row or column are outside the matrix dimensions.
   */
  [[nodiscard]] std::size_t index(std::size_t row, std::size_t col) const;

 public:
  /**
   * @brief Creates a matrix with the given dimensions and value.
   *
   * All elements are initialized with zero by default.
   *
   * @param rows Number of rows of the matrix.
   * @param cols Number of columns of the matrix.
   * @param initial_value Initial value to fill the matrix. Default value of 0.0.
   */
  Matrix(std::size_t rows, std::size_t cols, double initial_value = 0.0);

  /**
   * @brief Creates a matrix with the given nested initializer lists.
   *
   * @param values matrix values arranged by rows.
   *
   * @throws InvalidMatrixDimensions If a matrix rows do not have the same number of columns.
   */
  Matrix(std::initializer_list<std::initializer_list<double>> values);

  /**
   * @brief Creates a matrix with two vectors. Used in bindings for Python.
   *
   * @param values matrix values arranged by rows.
   *
   * @throws InvalidMatrixDimensions If a matrix rows do not have the same number of columns.
   */
  Matrix(std::vector<std::vector<double>> values);

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
   * @brief Fill the entire matrix with random values, using a uniform distribution.
   *
   * @param min_val The minimum number a chosen value can assume. Default value of 0.0.
   * @param max_val The maximum number a chosen value can assume. Default value of 1.0.
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
  [[nodiscard]] std::size_t rows() const;

  /**
   * @brief Returns the number of columns of the matrix.
   *
   * @returns Number of columns in matrix.
   */
  [[nodiscard]] std::size_t cols() const;

  /**
   * @brief Returns the sum of the entire matrix.
   *
   * @return The sum of the entire matrix.
   */
  [[nodiscard]] double sum() const;

  /**
   * @brief Returns a matrix with the sum of each axis in the matrix.
   *
   * Axis must be 0 or 1.
   * If axis = 0, sums down each column.
   * If axis = 1, sums across each row.
   *
   * @param axis Which direction to make the sum.
   *
   * @return A new matrix with the chosen axis sum. The shape of the resulting matrix will be (1,
   * cols) for axis = 0 and (rows, 1) for axis = 1.
   *
   * @throws InvalidAxis If the provided axis is not 0 or 1.
   */
  [[nodiscard]] Matrix sum(int axis) const;

  /**
   * @brief Returns the mean of the matrix.
   *
   * @return The mean of the matrix.
   */
  [[nodiscard]] double mean() const;

  /**
   * @brief Returns the maximum value in the matrix.
   *
   * @return The maximum value in the matrix.
   *
   * @throws InvalidAxis If the provided axis is not 0 or 1.
   */
  [[nodiscard]] double max() const;

  /**
   * @brief Returns a matrix with the maximum value in an axis.
   *
   * Axis must be 0 or 1
   * If axis = 0, computes the maximum column-wise.
   * If axis = 1, computes the maximum row-wise.
   *
   * @param axis Which direction to compute the maximum.
   *
   * @return A new matrix with the chosen axis maximum values. The shape of the resulting matrix
   * will be (1, cols) for axis = 0 and (rows, 1) for axis = 1.
   */
  [[nodiscard]] Matrix max(int axis) const;

  /**
   * @brief Multiply two matrices element-wise.
   *
   * @param other Matrix to multiply.
   *
   * @return A new matrix with the result of the multiplication.
   */
  [[nodiscard]] Matrix hadamard(const Matrix& other) const;

  /**
   * @brief Add two Matrices.
   *
   * It has overloaded behavior to add a row vector to each row of the matrix (broadcasting).
   * column vectors are not supported for broadcasting yet.
   *
   * @param other Matrix to add.
   *
   * @returns A new matrix with the result of the addition.
   *
   * @throws InvalidMatrixDimensions If the two matrices do not have the same dimensions.
   */
  Matrix operator+(const Matrix& other) const;

  /**
   * @brief Subtract two Matrices.
   *
   * @param other Matrix to subtract.
   *
   * @returns A new matrix with the result of the subtraction.
   *
   * @throws InvalidMatrixDimensions If the two matrices do not have the same dimensions.
   */
  Matrix operator-(const Matrix& other) const;

  /**
   * @brief Multiply two Matrices.
   *
   * @param other Matrix to multiply.
   *
   * @returns A new matrix with the result of the multiplication.
   *
   * @throws InvalidMatrixDimensions If the number of columns of the first matrix is not equal to
   * the number of rows of the second matrix.
   */
  Matrix operator*(const Matrix& other) const;

  /**
   * @brief Multiply all the given matrix values by a scalar number.
   *
   * This operator allows matrix * scalar multiply.
   *
   * @param scalar Number that will multiply the matrix.
   *
   * @returns A new matrix with the result of the multiplication.
   */
  Matrix operator*(double scalar) const;

  /**
   * @brief Divide all the given matrix values by a scalar number.
   *
   * This operator allows matrix / scalar divide.
   *
   * @param scalar Number that will divide the matrix.
   *
   * @returns A new matrix with the result of the division.
   *
   * @throws ZeroDivisionError If trying to divide by zero.
   */
  Matrix operator/(double scalar) const;

  /**
   * @brief Provides access to a matrix element using Matrix(row, column).
   *
   * This operator CAN modify a value. (e. g. A(1, 2) = 4.0).
   *
   * @param rows The row you want to access.
   * @param cols The column you want to access.
   *
   * @returns Element in the chosen position.
   *
   * @throws PositionNotInMatrix If the provided row or column are outside the matrix dimensions.
   */
  double& operator()(std::size_t rows, std::size_t cols);

  /**
   * @brief Provides access to a matrix element using Matrix(row, column).
   *
   * This operator CANNOT modify a value.
   *
   * @param rows The row you want to access.
   * @param cols The column you want to access.
   *
   * @returns Element in the chosen position.
   *
   * @throws PositionNotInMatrix If the provided row or column are outside the matrix dimensions.
   */
  double operator()(std::size_t rows, std::size_t cols) const;

  /**
   * @brief Compares two matrices for equality.
   *
   * @param other Matrix to compare.
   *
   * @returns True If the two matrices are the same.
   * @returns False If the two matrices have a difference.
   */
  bool operator==(const Matrix& other) const;

  /**
   * @brief Compares two matrices for inequality.
   *
   * @param other Matrix to compare.
   *
   * @returns True If the two matrices have a difference.
   * @returns False If the two matrices are the same.
   */
  bool operator!=(const Matrix& other) const;

  /**
   * @brief A factory function that returns a zero matrix.
   *
   * @param rows Number of rows of the matrix.
   * @param cols Number of columns of the matrix.
   *
   * @returns A Zero matrix.
   */
  static Matrix zeros(std::size_t rows, std::size_t cols);

  /**
   * @brief A factory function that returns a matrix filled with ones.
   *
   * @param rows Number of rows of the matrix.
   * @param cols Number of columns of the matrix.
   *
   * @returns A matrix filled with the number one.
   */
  static Matrix ones(std::size_t rows, std::size_t cols);

  /**
   * @brief A factory function that returns an identity matrix.
   *
   * @param size The size of the matrix (identity matrices must be square).
   *
   * @returns The identity matrix.
   */
  static Matrix identity(std::size_t size);

  /**
   * @brief A factory function that returns a matrix with random numbers, using a uniform
   * distribution.
   *
   * @param rows Number of rows of the matrix.
   * @param cols Number of columns of the matrix.
   * @param min_val The minimum number a chosen value can assume. Default value of 0.0.
   * @param max_val The maximum number a chosen value can assume. Default value of 1.0.
   *
   * @returns A matrix with random values.
   */
  static Matrix random(std::size_t rows, std::size_t cols, double min_val = 0.0,
                       double max_val = 1.0);

  /**
   * @brief Transposes the matrix.
   *
   * Swaps the matrix's rows and columns.
   *
   * @returns A new matrix that is the transpose of the original.
   */
  [[nodiscard]] Matrix transpose() const;

  /**
   * @brief It takes the logarithm of all the numbers in the matrix.
   *
   * The logarithm has base e.
   *
   * @return A new matrix with the result of the logarithm operations.
   *
   * @throws std::domain_error If the argument(s) of log(x) are not in the correct domain (x > 0).
   */
  [[nodiscard]] Matrix log() const;

  /**
   * @brief Calculate Euler's number (e) raised to the power of each number in the matrix (e^x).
   *
   * @return A new matrix with the result of the exponential operations.
   */
  [[nodiscard]] Matrix exp() const;

  /**
   * @brief Inserts a matrix into an output stream. It prints it in a human-readable format.
   *
   * e.g. std::cout << MatrixA.
   *
   * @param matrix The specified matrix.
   */
  friend std::ostream& operator<<(std::ostream& ostream, const Matrix& matrix);
};

/**
 * @brief Multiply all the given matrix values by a scalar number.
 *
 * This operator allows scalar * matrix multiply.
 *
 * @param scalar Number that will multiply the matrix.
 *
 * @returns A new matrix with the result of the multiplication.
 */
Matrix operator*(double scalar, const Matrix& matrix);
}  // namespace orion