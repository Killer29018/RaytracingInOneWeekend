#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "ray.hpp"
#include "general.hpp"

struct material;

struct hitRecord
{
    Point3 point;
    vec3 normal;
    std::shared_ptr<material> matPtr;
    double t;
    bool frontFace;

    inline void setFaceNormal(const Ray& r, const vec3& outwardNormal)
    {
        frontFace = dot(r.direction(), outwardNormal) < 0;
        normal = frontFace ? outwardNormal : -outwardNormal;
    }
};

class hittable
{
public:
    virtual bool hit(const Ray& r, double tMin, double tMax, hitRecord& rec) const = 0;
};

#endif