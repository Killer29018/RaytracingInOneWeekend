#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "general.hpp"
#include "hittable.hpp"

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
        vec3 scatterDirection = rec.normal + randomUnitVector();

        if (scatterDirection.nearZero())
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
        vec3 reflected = reflect(unitVector(r.direction()), rec.normal);
        scattered = Ray(rec.point, reflected + fuzz * randomInUnitSphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

#endif