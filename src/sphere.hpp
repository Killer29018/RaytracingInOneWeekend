#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "ray.hpp"
#include "vec3.hpp"

class sphere : public hittable
{
public:
    Point3 center;
    std::shared_ptr<material> matPtr;
    double radius;
public:
    sphere();
    sphere(Point3 cen, double r, std::shared_ptr<material> m) : center(cen), radius(r), matPtr(m) { }

    virtual bool hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const
    {
        vec3 oc = r.origin() - center;

        double a = r.direction().lengthSquared();
        double b = dot(oc, r.direction());
        double c = oc.lengthSquared() - radius*radius;

        double discriminant = b*b - a*c;
        if (discriminant < 0) return false;
        double sqrtd = std::sqrt(discriminant);

        double root = (-b - sqrtd) / a;
        if (root < tMin || tMax < root)
        {
            root = (-b + sqrtd) / a;
            if (root < tMin || tMax < root)
                return false;
        }

        rec.t = root;
        rec.point = r.at(rec.t);
        vec3 outwardNormal = (rec.point - center) / radius;
        rec.setFaceNormal(r, outwardNormal);
        rec.matPtr = matPtr;

        return true;
    }
};

#endif