#include <iostream>

#include "general.hpp"
#include "camera.hpp"

#include "colour.hpp"
#include "hittableList.hpp"
#include "material.hpp"
#include "sphere.hpp"

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

Colour rayColour(const Ray& r, const hittable& world, int depth);
hittableList randomScene();

int main()
{
    const double aspectRatio = 3.0 / 2.0;
    const int imageWidth = 1200;
    const int imageHeight = (int)(imageWidth / aspectRatio);
    const int samplesPerPixel = 500;
    const int maxDepth = 50;

    hittableList world = randomScene();

    Point3 lookFrom(13, 2, 3);
    Point3 lookAt(0, 0, 0);
    vec3 up(0, 1, 0);
    double distToFocus = 10.0; 
    double aperture = 0.1;
    camera cam(lookFrom, lookAt, up, 20, aspectRatio, aperture, distToFocus);

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

hittableList randomScene()
{
    hittableList world;

    auto groundMaterial = std::make_shared<lambertian>(Colour(0.5, 0.5, 0.5));
    world.add(std::make_shared<sphere>(Point3(0, -1000.0, 0), 1000, groundMaterial));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double chooseMat = randomDouble();
            Point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9)
            {
                std::shared_ptr<material> sphereMaterial;

                if (chooseMat < 0.8) // Diffuse
                {
                    vec3 albedo = Colour::random() * Colour::random();
                    sphereMaterial = std::make_shared<lambertian>(albedo);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95) // Metal
                {
                    vec3 albedo = Colour::random(0.5, 1);
                    double fuzz = randomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
                else // Glass
                {
                    sphereMaterial = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<dielectric>(1.5);
    world.add(std::make_shared<sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<lambertian>(Colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<sphere>(Point3(-4, 1, 0), 1.0, material2));
    
    auto material3 = std::make_shared<metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}