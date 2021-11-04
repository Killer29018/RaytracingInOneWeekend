#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "General.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

class Camera
{
private:
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;
    Vec3 u,v,w;
    double lensRadius;
public:
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 up, double vFOV, double aspectRatio, double aperture, double focusDist);

    Ray GetRay(double s, double t) const;
};

#endif