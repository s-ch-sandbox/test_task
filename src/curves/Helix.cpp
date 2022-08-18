#define _USE_MATH_DEFINES
#include "Helix.h"

#include <cmath>
#include <stdexcept>

namespace curves {
Helix::Helix(double radius, double step) : radius_{radius}, step_{step} {
    if (std::abs(radius_) < 1e-10) {
        throw std::invalid_argument("Helix radius must be a positive number");
    }
}

Vec3d Helix::ValueAt(const double t) const { return {radius_ * cos(t), radius_ * sin(t), t / (2 * M_PI) * step_}; }

Vec3d Helix::GradAt(const double t) const { return {-radius_ * sin(t), radius_ * cos(t), step_ / (2 * M_PI)}; }
}  // namespace curves
