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

        vec3 unitDirection = unitVector(r.direction());
        double cosTheta = fmin(dot(-unitDirection, rec.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta*cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        vec3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
            direction = reflect(unitDirection, rec.normal);
        else
            direction = refract(unitDirection, rec.normal, refractionRatio);

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