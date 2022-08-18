#pragma once
#include "Curve.h"


namespace curves {
class Ellipse : public Curve {
    public:
    Ellipse(double radius_x, double radius_y);

    Vec3d ValueAt(const double t) const override;
    Vec3d GradAt(const double t) const override;

    private:
    /* Ellipse radius along x-axis */
    double radius_x_;
    /* Ellipse radius along y-axis */
    double radius_y_;
};
}
