#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "General.hpp"
#include "Hittable.hpp"

struct hitRecord;

class material
{
public:
    virtual bool scatter(const Ray& rIn, const hitRecord& rec, Colour& attenuation, Ray& scattered) const = 0;
};

class lambertian : public material
{
public:
    Colour albedo;
public:
    lambertian(const Colour& a) : albedo(a) {}

    virtual bool scatter(const Ray& r, const hitRecord& rec, Colour& attenuation, Ray& scattered) const override
    {
        Vec3 scatterDirection = rec.normal + Vec3::RandomUnitVector();

        if (scatterDirection.NearZero())
            scatterDirection = rec.normal;

        scattered = Ray(rec.point, scatterDirection);
        attenuation = albedo;
        return true;
    }
};

class metal : public material
{
public:
    Colour albedo;
    double fuzz;
public:
    metal(const Colour& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

    virtual bool scatter(const Ray& r, const hitRecord& rec, Colour& attenuation, Ray& scattered) const override
    {
        Vec3 reflected = Vec3::Reflect(Vec3::UnitVector(r.direction()), rec.normal);
        scattered = Ray(rec.point, reflected + fuzz * Vec3::RandomInUnitSphere());
        attenuation = albedo;
        return (Vec3::Dot(scattered.direction(), rec.normal) > 0);
    }
};

class dielectric : public material
{
public:
    double ir;
public:
    dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

    virtual bool scatter(const Ray& r, const hitRecord& rec, Colour& attenuation, Ray& scattered) const override
    {
        attenuation = Colour(1.0, 1.0, 1.0);
        double refractionRatio = rec.frontFace ? (1.0 / ir) : ir;

        Vec3 unitDirection = Vec3::UnitVector(r.direction());
        double cosTheta = fmin(Vec3::Dot(-unitDirection, rec.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vec3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > RandomDouble())
            direction = Vec3::Reflect(unitDirection, rec.normal);
        else
            direction = Vec3::Refract(unitDirection, rec.normal, refractionRatio);

        scattered = Ray(rec.point, direction); 
        return true;
    }
private:
    static double reflectance(double cosine, double refIdx)
    {
        auto r0 = (1-refIdx) / (1+refIdx);
        r0 = r0*r0;
        return r0 + (1-r0)*pow((1 - cosine),5);
    }
};

#endif