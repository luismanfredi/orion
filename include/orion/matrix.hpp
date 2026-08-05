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

         friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) { 
            for(std::size_t i = 0; i < mat.rows_; i++){
                os << "|";

                for(std::size_t j = 0; j < mat.cols_; j++){
                    os << std::setw(4)<< mat.data_[i][j];
                }
            os << " |\n";
            }
            return os;
        }

        friend std::ostream& operator<<(std::ostream& os, const Matrix& mat) { 
            for(std::size_t i = 0; i < mat.rows_; i++){
                os << "|";

                for(std::size_t j = 0; j < mat.cols_; j++){
                    os << std::setw(4)<< mat.data_[i][j];
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
};