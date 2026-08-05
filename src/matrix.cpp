#include "include/orion/matrix.hpp"

#include <iomanip>
#include <string>

Matrix::Matrix(std::size_t r, std::size_t c) 
    : rows_(r), 
      cols_(c),
      data_(r * c, 0.0) {}

std::size_t Matrix::index(std::size_t row, std::size_t col) const {
    if(row >= rows_ || col >= cols_){
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