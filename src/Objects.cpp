#include "Objects.hpp"

Sphere::Sphere() {}

Sphere::Sphere(Point3 center, double radius, std::shared_ptr<Material> material)
    : center(center), matPtr(material), radius(radius) {}

bool Sphere::Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const
{
    Vec3 A = ray.Origin();
    Vec3 B = ray.Direction();

    Vec3 A_C = A - center;

    // b is half it's intended value which leads to reduced calculation cost
    double a = Vec3::Dot(B, B);
    double b = Vec3::Dot(B, A_C);
    double c = Vec3::Dot(A_C, A_C) - radius*radius;

    double discriminant = b*b - a*c;
    if (discriminant < 0) return false;
    double sqrtD = std::sqrt(discriminant);

    double tRoot = (-b - sqrtD) / a;
    if (tRoot < tMin || tRoot > tMax)
    {
        tRoot = (-b + sqrtD) / a;
        if (tRoot < tMin || tRoot > tMax)
            return false;
    }

    rec.t = tRoot;
    rec.point = ray.At(rec.t);
    Vec3 outwardNormal = (rec.point - center) / radius;
    rec.SetFaceNormal(ray, outwardNormal);
    rec.matPtr = matPtr;

    return true;
}


Plane::Plane() {}

Plane::Plane(Point3 orig, Vec3 normal, std::shared_ptr<Material> material)
    : orig(orig), normal(normal), matPtr(material) {}

bool Plane::Hit(const Ray& ray, double tMin, double tMax, HitRecord& rec) const
{
    double t = Vec3::Dot(-(normal), ray.Origin() - orig) / Vec3::Dot(normal, ray.Direction());

    if (t < tMin || t > tMax)
        return false;

    rec.t = t;
    rec.point = ray.At(rec.t);
    Vec3 outwardNormal = normal;
    rec.SetFaceNormal(ray, outwardNormal);
    rec.matPtr = matPtr;

    return true;
}