#pragma once

#include <ostream>


namespace curves {
struct Vec3d {
    double x;
    double y;
    double z;
};

std::ostream& operator<<(std::ostream& os, const Vec3d& v);

/*
    Base class for curves.
    Each curve must implement ValueAt() and GradAt() functions.
*/
class Curve {
public:
    /* Get point of curve (x,y,z) for parameter value t */
    virtual Vec3d ValueAt(const double t) const = 0;
    /* Get gradient value (dx/dt, dy/dt, dz/dt) for parameter value t */
    virtual Vec3d GradAt(const double t) const = 0;
    virtual ~Curve() = default;
};
}
