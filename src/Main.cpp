#include <iostream>

#include "general.hpp"
#include "camera.hpp"

#include "colour.hpp"
#include "hittableList.hpp"
#include "material.hpp"
#include "sphere.hpp"

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

Colour rayColour(const Ray& r, const hittable& world, int depth);

int main()
{
    const double aspectRatio = 16.0 / 9.0;
    const int imageWidth = 400;
    const int imageHeight = (int)(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    hittableList world;

    std::shared_ptr<lambertian> materialGround = std::make_shared<lambertian>(Colour(0.8, 0.8, 0.0));
    std::shared_ptr<lambertian> materialCenter = std::make_shared<lambertian>(Colour(0.7, 0.3, 0.3));
    std::shared_ptr<metal> materialLeft = std::make_shared<metal>(Colour(0.8, 0.8, 0.8), 0.3);
    std::shared_ptr<metal> materialRight = std::make_shared<metal>(Colour(0.8, 0.6, 0.2), 1.0);

    world.add(std::make_shared<sphere>(Point3(0.0, -100.5, -1.0), 100.0, materialGround));
    world.add(std::make_shared<sphere>(Point3(0.0, 0.0, -1.0), 0.5, materialCenter));
    world.add(std::make_shared<sphere>(Point3(-1.0, 0.0, -1.0), 0.5, materialLeft));
    world.add(std::make_shared<sphere>(Point3(1.0, 0.0, -1.0), 0.5, materialRight));

    camera cam;

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; j--)
    {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            Colour pixelColour(0, 0, 0);
            for (int x = 0; x < samplesPerPixel; x++)
            {
                double u = (i + randomDouble()) / (imageWidth-1);
                double v = (j + randomDouble()) / (imageHeight-1);
                Ray r = cam.getRay(u, v);
                pixelColour += rayColour(r, world, maxDepth);
            }
            writeColour(std::cout, pixelColour, samplesPerPixel);
        }
    }
    std::cerr << "\nDone\n";

    return 0;
}

Colour rayColour (const Ray& r, const hittable& world, int depth)
{
    hitRecord rec;

    if (depth <= 0)
        return Colour(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Colour attenuation;
        if (rec.matPtr->scatter(r, rec, attenuation, scattered))
            return attenuation * rayColour(scattered, world, depth - 1);
        return Colour(0, 0, 0);
    }

    vec3 unitDirection = unitVector(r.direction());
    double t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Colour(1, 1, 1) + t * Colour(0.5, 0.7, 1.0);
}
