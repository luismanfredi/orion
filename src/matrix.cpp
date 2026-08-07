#include "orion/matrix.hpp"

#include <iomanip>
#include <string>

Matrix::Matrix(std::size_t r, std::size_t c, double initial_value) 
    : rows_(r), 
      cols_(c),
      data_(r * c, initial_value) {}

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
        for (const double value: row) {
            data_.push_back(value);
        }
    }
}

std::size_t Matrix::index(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw PositionNotInMatrix(
            "Position (" +
            std::to_string(row) + ", " +
            std::to_string(col) + 
            ") is outside matrix dimensions (" +
            std::to_string(rows_) + " x " +
            std::to_string(cols_) + ")."
        );
    }
    return row * cols_ + col;
}

void Matrix::set(std::size_t r, std::size_t c, double val) {
    data_[index(r, c)] = val;
}

double Matrix::get(std::size_t r, std::size_t c) const {
    return data_[index(r, c)];
}

Matrix Matrix::fill(double value) {
    Matrix result(rows_, cols_);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(i, j, value);
        }
    }
    return result;
}

std::size_t Matrix::rows() const {
    return rows_;
}

std::size_t Matrix::cols() const {
    return cols_;
}

Matrix Matrix::operator+(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw InvalidMatrixDimensions("Matrix must be same dimensions!");
    }

    Matrix result(rows_, cols_);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(i, j, get(i, j) + other.get(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        throw InvalidMatrixDimensions("Matrix must be same dimensions!");
    }

    Matrix result(rows_, cols_);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(i, j, get(i, j) - other.get(i, j));
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw InvalidMatrixDimensions(
            "The number of columns of the first Matrix must be equal the number of rows of the second Matrix"
        );
    }

    Matrix result(rows_, other.cols_);

    for (std::size_t i = 0; i < rows_; i++) {
        for (std::size_t j = 0; j < other.cols_; j++) {
            double sum = 0;
            for (std::size_t k = 0; k < cols_; k++) {
                sum += get(i, k) * other.get(k, j);
            }
            result .set(i, j, sum);
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(rows_, cols_);

    for (std::size_t i = 0; i < rows_; ++i) {
        for (std::size_t j = 0; j < cols_; ++j) {
            result.set(i, j, get(i, j) * scalar);
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& matrix){
    return matrix * scalar;
}

Matrix Matrix::transpose() const{
    Matrix result(cols_, rows_);

    for (std::size_t i = 0; i < rows_; ++i){
        for (std::size_t j = 0; j < cols_; ++j){
            result.set(j, i, get(i, j));
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& mat) { 
    for (std::size_t i = 0; i < mat.rows_; ++i) {
        os << "|";

        for (std::size_t j = 0; j < mat.cols_; ++j) {
            os << std::setw(8)<< mat.get(i, j);
        }
    os << " |\n";
    }
    return os;
}