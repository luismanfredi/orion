#pragma once

#include <exception>
#include <string>

#include "BaseException.hpp"

namespace orion {

class DomainError : public Exception {
 public:
  explicit DomainError(const std::string& msg) : Exception("Math Error: " + msg) {}
};

class ZeroDivisionError : public Exception {
 public:
  explicit ZeroDivisionError(const std::string& msg) : Exception("Math Error: " + msg) {}
};

}  // namespace orion