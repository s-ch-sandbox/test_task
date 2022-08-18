#pragma once
#include "Curve.h"


namespace curves {
class Circle : public Curve {
    public:
    explicit Circle(double radius);

    Vec3d ValueAt(const double t) const override;
    Vec3d GradAt(const double t) const override;
    double GetRadius() const;

    private:
    /* Circle radius */
    double radius_;
};
}
