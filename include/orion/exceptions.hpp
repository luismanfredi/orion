#pragma once

#include <string>
#include <exception>

class PositionNotInMatrix : public std::exception {
    private:
        std::string message;

    public:
        explicit PositionNotInMatrix(const std::string& msg) : message(msg) {}

        const char* what() const noexcept override {
            return message.c_str();
        }
};