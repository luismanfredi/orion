#pragma once

#include <ostream>
#include <vector>
#include <iomanip>
#include <initializer_list>

#include "exceptions/MatrixExceptions.hpp"

namespace Orion{
    class Matrix {
        private:
            std::size_t rows_;
            std::size_t cols_;
            std::vector<double> data_;

            std::size_t index(std::size_t row, std::size_t col) const;

        public:
            Matrix(std::size_t r, std::size_t c, double initial_value = 0.0);
            Matrix(std::initializer_list<std::initializer_list<double>> values);

            void set(std::size_t r, std::size_t c, double val);
            double get(std::size_t r, std::size_t c) const;

            void fill(double value = 0.0);
            void fillRange(double start, double step = 1.0);

            std::size_t rows() const;
            std::size_t cols() const;

            Matrix operator+(const Matrix& other) const;
            Matrix operator-(const Matrix& other) const;
            Matrix operator*(const Matrix& other) const;
            Matrix operator*(double scalar) const;

            bool operator==(const Matrix& other) const;

            Matrix transpose() const;

            friend std::ostream& operator<<(std::ostream&, const Matrix&);
    };

    Matrix operator*(double scalar, const Matrix& matrix);
}