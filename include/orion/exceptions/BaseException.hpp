#pragma once

#include <stdexcept>

namespace orion {
    class Exception : public std::runtime_error {
        public:
            using std::runtime_error::runtime_error;
    };
}