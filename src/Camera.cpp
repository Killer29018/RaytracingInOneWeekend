#include "Camera.hpp"

Camera::Camera(Point3 lookFrom, Point3 lookAt, Vec3 up, double vFOV, double aspectRatio, double aperture, double focusDist)
{
    double theta = DegreesToRadians(vFOV);
    double h = tan(theta/2);
    double viewportHeight = 2.0 * h;
    double viewportWidth = aspectRatio * viewportHeight;

    double focalLength = 1.0;

    Vec3 w = Vec3::UnitVector(lookFrom - lookAt);
    Vec3 u = Vec3::UnitVector(Vec3::Cross(up, w));
    Vec3 v = Vec3::Cross(w, u); 

    origin = lookFrom; 
    horizontal = focusDist * viewportWidth * u; 
    vertical = focusDist * viewportHeight * v; 
    lowerLeftCorner = origin - horizontal/2 - vertical/2 - focusDist*w; 

    lensRadius = aperture / 2;
}

Ray Camera::GetRay(double s, double t) const
{
    Vec3 rd = lensRadius * Vec3::RandomInUnitDisc();
    Vec3 offset = u * rd.x() + v * rd.y();

    return Ray(origin + offset, lowerLeftCorner + s*horizontal + t*vertical - origin - offset);
}