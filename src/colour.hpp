#ifndef COLOUR_HPP
#define COLOUR_HPP

#include "Vec3.hpp"
#include "General.hpp"

#include <iostream>

void writeColour(std::ostream& out, Colour pixelColour)
{
    out << static_cast<int>(255.999 * pixelColour.x()) << " "
    << static_cast<int>(255.999 * pixelColour.y()) << " "
    << static_cast<int>(255.999 * pixelColour.z()) << "\n";
}

void writeColour(std::ostream& out, Colour pixelColour, int samplesPerPixel)
{
    double r = pixelColour.x();
    double g = pixelColour.y();
    double b = pixelColour.z();

    double scale = 1.0 / samplesPerPixel;
    r = std::sqrt(scale * r);
    g = std::sqrt(scale * g);
    b = std::sqrt(scale * b);

    out << (int)(256 * Clamp(r, 0.0, 0.999)) << " "
        << (int)(256 * Clamp(g, 0.0, 0.999)) << " "
        << (int)(256 * Clamp(b, 0.0, 0.999)) << "\n";
}

#endif