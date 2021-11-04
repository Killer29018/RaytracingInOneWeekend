#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>
#include "General.hpp"

class Vec3
{
public:
    double e[3];
public:
    Vec3(); 
    Vec3(double x, double y, double z);

    double x() const; 
    double y() const;
    double z() const;

    static Vec3 Random();
    static Vec3 Random(double min, double max);
    bool NearZero() const;

    double Length() const;
    double LengthSquared() const;

    static double Dot(const Vec3& v, const Vec3& u);
    static Vec3 RandomInUnitSphere();
    static Vec3 RandomUnitVector();
    static Vec3 RandomInHemisphere(const Vec3& normal);
    static Vec3 RandomInUnitDisc();
    static Vec3 Reflect(const Vec3& v, const Vec3& n);
    static Vec3 Refract(const Vec3& uv, const Vec3& n, double etaiOverEtat);
    static Vec3 Cross(const Vec3& v, const Vec3& u);
    static Vec3 UnitVector(Vec3 v);

    Vec3 operator-() const; 
    double operator[](int i) const;
    double& operator[](int i);
    Vec3& operator+=(const Vec3 &v);
    Vec3& operator*=(const double t);
    Vec3& operator/=(const double t);
};

using Point3 = Vec3;
using Colour = Vec3;

inline std::ostream& operator<<(std::ostream& out, const Vec3& v)
{
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline Vec3 operator+(const Vec3& v, const Vec3& u)
{
    return Vec3(v.e[0] + u.e[0], v.e[1] + u.e[1], v.e[2] + u.e[2]);
}

inline Vec3 operator-(const Vec3& v, const Vec3& u)
{
    return Vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

inline Vec3 operator*(const Vec3& v, const Vec3& u)
{
    return Vec3(v.e[0] * u.e[0], v.e[1] * u.e[1], v.e[2] * u.e[2]);
}

inline Vec3 operator*(const Vec3& v, double t)
{
    return Vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline Vec3 operator*(double t, const Vec3& v)
{
    return v * t;
}

inline Vec3 operator/(const Vec3& v, double t)
{
    return v * (1/t);
}

#endif