#pragma once

#include <string>
#include <exception>
#include "BaseException.hpp"

namespace Orion {
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

class InvalidMatrixDimensions : public std::exception {
    private:
        std::string message;

    public:
        explicit InvalidMatrixDimensions(const std::string& msg) : message(msg) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
};

class PositionNotInMatrix : public std::exception {
    private:
        std::string message;

    public:
        explicit PositionNotInMatrix(const std::string& msg) : message(msg) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
};