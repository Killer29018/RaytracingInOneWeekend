#ifndef RAY_HPP
#define RAY_HPP

#include "vec3.hpp"

class Ray
{
public:
    Point3 orig;
    vec3 dir;
public:
    Ray() {};
    Ray(const Point3& origin, const Point3& direction)
        : orig(origin), dir(direction) {}

    Point3 origin() const { return orig; }
    vec3 direction() const { return dir; }

    Point3 at(double t) const { return orig + t * dir; }
};

#endif