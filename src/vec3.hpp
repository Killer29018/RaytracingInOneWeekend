#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

class vec3
{
public:
    double e[3];
public:
    vec3() : e{0, 0, 0} {}
    vec3(double x, double y, double z) : e{x, y, z} {}

    double x() const {return e[0]; }
    double y() const {return e[1]; }
    double z() const {return e[2]; }

    inline static vec3 random()
    {
        return vec3(randomDouble(), randomDouble(), randomDouble());
    }

    inline static vec3 random(double min, double max)
    {
        return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
    }

    bool nearZero() const 
    {
        const double s = 1e-8;
        return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
    }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    double operator[](int i) const { return e[i]; }
    double& operator[](int i) { return e[i]; }

    vec3& operator+=(const vec3 &v)
    {
        e[0] += v.e[0];
        e[1] += v.e[1];
        e[2] += v.e[2];
        return *this;
    }

    vec3& operator*=(const double t)
    {
        e[0] *= t;
        e[1] *= t;
        e[2] *= t;
        return *this;
    }

    vec3& operator/=(const double t)
    {
        return *this *= 1/t;
    }

    double length() const 
    {
        return std::sqrt(lengthSquared());
    }

    double lengthSquared() const
    {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }
};

using Point3 = vec3;
using Colour = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.e[0] << " " << v.e[1] << " " << v.e[2];
}

inline vec3 operator+(const vec3& v, const vec3& u)
{
    return vec3(v.e[0] + u.e[0], v.e[1] + u.e[1], v.e[2] + u.e[2]);
}

inline vec3 operator-(const vec3& v, const vec3& u)
{
    return vec3(v.e[0] - u.e[0], v.e[1] - u.e[1], v.e[2] - u.e[2]);
}

inline vec3 operator*(const vec3& v, const vec3& u)
{
    return vec3(v.e[0] * u.e[0], v.e[1] * u.e[1], v.e[2] * u.e[2]);
}

inline vec3 operator*(const vec3& v, double t)
{
    return vec3(v.e[0] * t, v.e[1] * t, v.e[2] * t);
}

inline vec3 operator*(double t, const vec3& v)
{
    return v * t;
}

inline vec3 operator/(const vec3& v, double t)
{
    return v * (1/t);
}

inline double dot(const vec3& v, const vec3& u)
{
    return v.e[0] * u.e[0] +
        v.e[1] * u.e[1] + 
        v.e[2] * u.e[2];
}

inline vec3 cross(const vec3& v, const vec3& u)
{
    return vec3(v.e[1] * u.e[2] - v.e[2] * u.e[1],
        v.e[2] * u.e[0] - v.e[0] * u.e[2],
        v.e[0] * u.e[1] - v.e[1] * u.e[0]);
}

inline vec3 unitVector(vec3 v)
{
    return v / v.length();
}

vec3 randomInUnitSphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1, 1);
        if (p.lengthSquared() >= 1) continue;
        return p;
    }
}

vec3 randomUnitVector()
{
    return unitVector(randomInUnitSphere());
}

vec3 randomInHemisphere(const vec3& normal)
{
    vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0)
        return inUnitSphere;
    else
        return -inUnitSphere;
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

#endif