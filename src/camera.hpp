#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "general.hpp"

class camera
{
private:
    Point3 origin;
    Point3 lowerLeftCorner;
    vec3 horizontal;
    vec3 vertical;
public:
    camera() 
    {
        double aspectRatio = 16.0 / 9.0;
        double viewportHeight = 2.0;
        double viewportWidth = aspectRatio * viewportHeight;
        double focalLength = 1.0;

        origin = Point3(0, 0, 0);
        horizontal = vec3(viewportWidth, 0.0, 0.0);
        vertical = vec3(0.0, viewportHeight, 0.0);
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - vec3(0, 0, focalLength);
    }

    Ray getRay(double u, double v) const{
        return Ray(origin, lowerLeftCorner + u*horizontal + v*vertical - origin);
    }
};

#endif