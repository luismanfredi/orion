#pragma once

#include <ostream>
#include <vector>
#include <iomanip>

class Matrix {
    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> data_;

        std::size_t index(std::size_t row, std::size_t col) const{
            return row * cols_ + col;
        }

    public:
        Matrix(std::size_t r, std::size_t c) : rows_(r), cols_(c), data_(r * c, 0.0) {}

        void set(std::size_t r, std::size_t c, double val){
            data_.at((index(r, c))) = val;
        }

        double get(std::size_t r, std::size_t c) const{
            return data_.at((index(r, c)));
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) { 
            for(std::size_t i = 0; i < mat.rows_; i++){
                os << "|";

                for(std::size_t j = 0; j < mat.cols_; j++){
                    os << std::setw(4)<< mat.get(i, j);
                }
            os << " |\n";
            }
            return os;
        }

        std::size_t rows() const{
            return rows_;
        }

        std::size_t cols() const{
            return cols_;
        }

        Matrix operator+(const Matrix&) const;

        Matrix transpose() const;

        double determinant() const;
};