#pragma once

#include <algorithm>
#include <cmath>

#include "constants.hpp"

namespace orion {

inline bool nearlyEqual(double a, double b, double absTol = kAbsTol, double relTol = kRelTol) {
  const double diff = std::abs(a - b);

  return diff <= std::max(absTol, relTol * std::max(std::abs(a), std::abs(b)));
}

}  // namespace orion