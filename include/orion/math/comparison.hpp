#pragma once

#include <algorithm>
#include <cmath>

#include "constants.hpp"

namespace Orion {

inline bool nearlyEqual(
    double a,
    double b,
    double absTol = ABS_TOL,
    double relTol = REL_TOL
) {
    const double diff = std::abs(a - b);

    return diff <= std::max(
        absTol,
        relTol * std::max(std::abs(a), std::abs(b))
    );
}

}