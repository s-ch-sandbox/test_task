#include "Ellipse.h"

#include <cmath>
#include <stdexcept>

namespace curves {
Ellipse::Ellipse(double radius_x, double radius_y) : radius_x_{radius_x}, radius_y_{radius_y} {
    if (std::abs(radius_x_) < 1e-10 || std::abs(radius_y_) < 1e-10) {
        throw std::invalid_argument("Ellipse radii must be positive numbers");
    }
}

Vec3d Ellipse::ValueAt(const double t) const { return {radius_x_ * cos(t), radius_y_ * sin(t), 0}; }

Vec3d Ellipse::GradAt(const double t) const { return {-radius_x_ * sin(t), radius_y_ * cos(t), 0}; }
}  // namespace curves
