#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable
{
public:
    Point3 center;
    std::shared_ptr<Material> matPtr;
    double radius;
public:
    Sphere();
    Sphere(Point3 cen, double r, std::shared_ptr<Material> m);

    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const;
};

#endif