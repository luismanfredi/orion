#include "include/orion/matrix.hpp"

#include <iomanip>
#include <string>

Matrix::Matrix(std::size_t r, std::size_t c) 
    : rows_(r), 
      cols_(c),
      data_(r * c, 0.0) {}