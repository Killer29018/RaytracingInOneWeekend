#ifndef RAY_HPP
#define RAY_HPP

#include "Vec3.hpp"

class Ray
{
public:
    Point3 orig;
    Vec3 dir;
public:
    Ray();
    Ray(const Point3& origin, const Point3& direction);

    Point3 Origin() const;
    Vec3 Direction() const;

    Point3 At(double t) const;
};

#endif