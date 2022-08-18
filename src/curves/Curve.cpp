#include "Curve.h"

#include <string>


namespace curves {
std::ostream& operator<<(std::ostream& os, const Vec3d& v) {
    os << std::string{"["} + std::to_string(v.x) + "; " + std::to_string(v.y) + ", " + std::to_string(v.z) + "]";
    return os;
}
}  // namespace curves
