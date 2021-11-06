#include "Sphere.hpp"

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

    double root = (-b - sqrtD) / a;
    if (root < tMin || tMax < root)
    {
        root = (-b + sqrtD) / a;
        if (root < tMin || tMax < root)
            return false;
    }

    rec.t = root;
    rec.point = ray.At(rec.t);
    Vec3 outwardNormal = (rec.point - center) / radius;
    rec.SetFaceNormal(ray, outwardNormal);
    rec.matPtr = matPtr;

    return true;
}