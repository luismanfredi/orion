#pragma once

#include <ostream>
#include <vector>
#include <iomanip>

class Matrix {
    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<std::vector<double>> data_;

    public:

        Matrix(std::size_t r, std::size_t c) : rows_(r), cols_(c), data_(r, std::vector<double>(c, 0.0)) {}

        void set(std::size_t r, std::size_t c, double val){
            data_.at(r).at(c) = val;
        }

        double get(std::size_t r, std::size_t c) const{
            return data_.at(r).at(c);
        }
};