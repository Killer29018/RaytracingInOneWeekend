#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "General.hpp"
#include "Hittable.hpp"

struct HitRecord;

class Material
{
public:
    virtual bool Scatter(const Ray& rIn, const HitRecord& rec, Colour& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material
{
public:
    Colour albedo;
public:
    Lambertian(const Colour& a);

    virtual bool Scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;
};

class Metal : public Material
{
public:
    Colour albedo;
    double fuzz;
public:
    Metal(const Colour& a, double f);

    virtual bool Scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;
};

class Dielectric : public Material
{
public:
    double ir;
public:
    Dielectric(double indexOfRefraction);

    virtual bool Scatter(const Ray& r, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override;
private:
    static double Reflectance(double cosine, double refIdx);
};

#endif