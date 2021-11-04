#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Ray.hpp"
#include "General.hpp"

struct Material;

struct hitRecord
{
    Point3 point;
    Vec3 normal;
    std::shared_ptr<Material> matPtr;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& r, const Vec3& outwardNormal)
    {
        frontFace = Vec3::Dot(r.Direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
    virtual bool hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const = 0;
};

#endif