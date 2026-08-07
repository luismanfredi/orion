#pragma once

#include <string>
#include <exception>
#include "BaseException.hpp"

namespace orion {
    class InvalidMatrixDimensions : public Exception {
        public:
            explicit InvalidMatrixDimensions(const std::string& msg)
                : Exception("Matrix Error: " + msg) {}
    };

    class PositionNotInMatrix : public Exception {
    public:
        explicit PositionNotInMatrix(const std::string& msg) 
            : Exception("Matrix Error: " + msg) {}
    };
}
