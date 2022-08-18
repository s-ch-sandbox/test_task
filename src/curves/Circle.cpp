#include "Circle.h"

#include <cmath>
#include <iostream>
#include <stdexcept>

namespace curves {
Circle::Circle(double radius) : radius_{radius} {
    if (std::abs(radius_) < 1e-10) {
        throw std::invalid_argument("Circle radius must be a positive number");
    }
}

Vec3d Circle::ValueAt(const double t) const { return {radius_ * cos(t), radius_ * sin(t), 0}; }

Vec3d Circle::GradAt(const double t) const { return {-radius_ * sin(t), radius_ * cos(t), 0}; }

double Circle::GetRadius() const { return radius_; }
}  // namespace curves
