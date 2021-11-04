#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Hittable.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"

class sphere : public hittable
{
public:
    Point3 center;
    std::shared_ptr<Material> matPtr;
    double radius;
public:
    sphere();
    sphere(Point3 cen, double r, std::shared_ptr<Material> m) : center(cen), radius(r), matPtr(m) { }

    virtual bool hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const
    {
        Vec3 oc = r.Origin() - center;

        double a = r.Direction().LengthSquared();
        double b = Vec3::Dot(oc, r.Direction());
        double c = oc.LengthSquared() - radius*radius;

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
        rec.point = r.At(rec.t);
        Vec3 outwardNormal = (rec.point - center) / radius;
        rec.setFaceNormal(r, outwardNormal);
        rec.matPtr = matPtr;

        return true;
    }
};

#endif