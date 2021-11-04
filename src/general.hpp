#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592563589;

inline double DegreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double RandomDouble(double min, double max)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double RandomDouble()
{
    return RandomDouble(0.0, 1.0);
}

inline double Clamp(double x, double min, double max)
{
    return std::min(std::max(min, x), max);
}

#endif