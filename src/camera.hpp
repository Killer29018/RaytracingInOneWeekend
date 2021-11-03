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
    vec3 u,v,w;
    double lensRadius;
public:
    camera(Point3 lookFrom, Point3 lookAt, vec3 up, double vFOV, double aspectRatio, double aperture, double focusDist)
    {
        double theta = degreesToRadians(vFOV);
        double h = tan(theta/2);
        double viewportHeight = 2.0 * h;
        double viewportWidth = aspectRatio * viewportHeight;

        double focalLength = 1.0;

        vec3 w = unitVector(lookFrom - lookAt);
        vec3 u = unitVector(cross(up, w));
        vec3 v = cross(w, u); 

        origin = lookFrom; 
        horizontal = focusDist * viewportWidth * u; 
        vertical = focusDist * viewportHeight * v; 
        lowerLeftCorner = origin - horizontal/2 - vertical/2 - focusDist*w; 

        lensRadius = aperture / 2;
    }

    Ray getRay(double s, double t) const
    {
        vec3 rd = lensRadius * randomInUnitDisc();
        vec3 offset = u * rd.x() + v*rd.y();

        return Ray(origin + offset, lowerLeftCorner + s*horizontal + t*vertical - origin - offset);
    }
};

#endif