#ifndef GENERAL_HPP
#define GENERAL_HPP

#include <cmath>
#include <limits>
#include <memory>
#include <cstdlib>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.141592563589;

inline double degreesToRadians(double degrees)
{
    return degrees * pi / 180.0;
}

inline double randomDouble(double min, double max)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble()
{
    return randomDouble(0.0, 1.0);
}

inline double clamp(double x, double min, double max)
{
    return std::min(std::max(min, x), max);
}

#include "ray.hpp"
#include "vec3.hpp"

#endif