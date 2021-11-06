#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "General.hpp"

struct Material;

struct HitRecord
{
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Material> matPtr;
    double t;
    bool frontFace;

    inline void SetFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        frontFace = Vec3::Dot(r.Direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class Hittable
{
public:
    virtual bool Hit(const Ray& r, double tMin, double tMax, HitRecord& rec) const = 0;
};

#endif