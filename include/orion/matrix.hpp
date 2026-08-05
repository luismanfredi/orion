#pragma once

#include <ostream>
#include <vector>
#include <iomanip>
#include "exceptions.hpp"

class Matrix {
    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> data_;

        std::size_t index(std::size_t row, std::size_t col) const;

    public:
        Matrix(std::size_t r, std::size_t c);

        void set(std::size_t r, std::size_t c, double val);
        double get(std::size_t r, std::size_t c) const;

        std::size_t rows() const{
            return rows_;
        }

        std::size_t cols() const{
            return cols_;
        }

        Matrix operator+(const Matrix&) const;
        Matrix transpose() const;
        double determinant() const;

        friend std::ostream& operator<<(std::ostream&, const Matrix&);
};