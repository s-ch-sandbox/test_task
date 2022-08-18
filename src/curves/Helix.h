#pragma once
#include "Curve.h"


namespace curves {
class Helix : public Curve {
    public:
    Helix(double radius, double step);

    Vec3d ValueAt(const double t) const override;
    Vec3d GradAt(const double t) const override;

    private:
    /* Helix radius (along x and y axes) */
    double radius_;
    /* Helix step along z-axis */
    double step_;
};
}
