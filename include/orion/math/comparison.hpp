#pragma once

#include <algorithm>
#include <cmath>

#include "constants.hpp"

namespace orion {

inline bool nearlyEqual(double num1, double num2, double absTol = kAbsTol,
                        double relTol = kRelTol) {
  const double diff = std::abs(num1 - num2);

  return diff <= std::max(absTol, relTol * std::max(std::abs(num1), std::abs(num2)));
}

}  // namespace orion