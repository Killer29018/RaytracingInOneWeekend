#include "Vec3.hpp"

Vec3::Vec3() : e{0, 0, 0} {}
Vec3::Vec3(double x, double y, double z) : e{x, y, z} {}

double Vec3::x() const {return e[0]; }
double Vec3::y() const {return e[1]; }
double Vec3::z() const {return e[2]; }

Vec3 Vec3::Random()
{
    return Vec3(RandomDouble(), RandomDouble(), RandomDouble());
}

Vec3 Vec3::Random(double min, double max)
{
    return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
}

bool Vec3::NearZero() const
{
    const double s = 1e-8;
    return (fabs(e[0]) < s) && (fabs(e[1]) < s) && (fabs(e[2]) < s);
}

double Vec3::Length() const
{
    return std::sqrt(LengthSquared());
}

double Vec3::LengthSquared() const
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}

double Vec3::Dot(const Vec3& v, const Vec3& u)
{
    return v.e[0] * u.e[0] +
        v.e[1] * u.e[1] +
        v.e[2] * u.e[2];
}

Vec3 Vec3::Cross(const Vec3& v, const Vec3& u)
{
    return Vec3(v.e[1] * u.e[2] - v.e[2] * u.e[1],
        v.e[2] * u.e[0] - v.e[0] * u.e[2],
        v.e[0] * u.e[1] - v.e[1] * u.e[0]);
}

Vec3 Vec3::UnitVector(Vec3 v)
{
    return v / v.Length();
}

Vec3 Vec3::RandomInUnitSphere()
{
    while (true)
    {
        Vec3 p = Vec3::Random(-1, 1);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

Vec3 Vec3::RandomUnitVector()
{
    return UnitVector(RandomInUnitSphere());
}

Vec3 Vec3::RandomInHemisphere(const Vec3& normal)
{
    Vec3 inUnitSphere = RandomInUnitSphere();
    if (Dot(inUnitSphere, normal) > 0.0)
        return inUnitSphere;
    else
        return -inUnitSphere;
}

Vec3 Vec3::RandomInUnitDisc()
{
    while (true)
    {
        Vec3 p = Vec3(RandomDouble(-1, 1), RandomDouble(-1, 1), 0);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

Vec3 Vec3::Reflect(const Vec3& v, const Vec3& n)
{
    return v-2 * Dot(v, n) * n;
}

Vec3 Vec3::Refract(const Vec3& uv, const Vec3& n, double etaiOverEtat)
{
    auto cosTheta = fmin(Dot(-uv, n), 1.0);
    Vec3 rOutPerp = etaiOverEtat * (uv + cosTheta*n);
    Vec3 rOutParralel = -sqrt(fabs(1.0 - rOutPerp.LengthSquared())) * n;
    return rOutPerp + rOutParralel; 
}

Vec3 Vec3::operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
double Vec3::operator[](int i) const { return e[i]; }
double& Vec3::operator[](int i) { return e[i]; }

Vec3& Vec3::operator+=(const Vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Vec3& Vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Vec3& Vec3::operator/=(const double t)
{
    return *this *= 1/t;
}