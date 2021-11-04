#include "Material.hpp"

Lambertian::Lambertian(const Colour& a)
    : albedo(a) {}


bool Lambertian::Scatter(const Ray& r, const hitRecord& rec, Colour& attenuation, Ray& scattered) const
{
    Vec3 scatterDirection = rec.normal + Vec3::RandomUnitVector();

    if (scatterDirection.NearZero())
        scatterDirection = rec.normal;

    scattered = Ray(rec.point, scatterDirection);
    attenuation = albedo;
    return true;
}

Metal::Metal(const Colour& a, double f)
    : albedo(a), fuzz(f < 1 ? f : 1) {}


bool Metal::Scatter(const Ray& r, const hitRecord& rec, Colour& attenuation, Ray& scattered) const
{
    Vec3 reflected = Vec3::Reflect(Vec3::UnitVector(r.Direction()), rec.normal);
    scattered = Ray(rec.point, reflected + fuzz * Vec3::RandomInUnitSphere());
    attenuation = albedo;
    return (Vec3::Dot(scattered.Direction(), rec.normal) > 0);
}


Dielectric::Dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

bool Dielectric::Scatter(const Ray& r, const hitRecord& rec, Colour& attenuation, Ray& scattered) const
{
    attenuation = Colour(1.0, 1.0, 1.0);
    double refractionRatio = rec.frontFace ? (1.0 / ir) : ir;

    Vec3 unitDirection = Vec3::UnitVector(r.Direction());
    double cosTheta = fmin(Vec3::Dot(-unitDirection, rec.normal), 1.0);
    double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

    bool cannotRefract = refractionRatio * sinTheta > 1.0;
    Vec3 direction;

    if (cannotRefract || Reflectance(cosTheta, refractionRatio) > RandomDouble())
        direction = Vec3::Reflect(unitDirection, rec.normal);
    else
        direction = Vec3::Refract(unitDirection, rec.normal, refractionRatio);

    scattered = Ray(rec.point, direction);
    return true;
}

double Dielectric::Reflectance(double cosine, double refIdx)
{
    auto r0 = (1-refIdx) / (1+refIdx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}