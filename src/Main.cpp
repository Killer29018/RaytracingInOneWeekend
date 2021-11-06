#include <iostream>

#include "Vec3.hpp"
#include "Ray.hpp"
#include "General.hpp"
#include "Camera.hpp"

#include "Colour.hpp"
#include "HittableList.hpp"
#include "Material.hpp"
#include "Sphere.hpp"

// https://raytracing.github.io/books/RayTracingInOneWeekend.html

Colour rayColour(const Ray& r, const Hittable& world, int depth);
HittableList randomScene();
HittableList basicScene();

int main()
{
    const double aspectRatio = 3.0 / 2.0;
    const int imageWidth = 400;
    const int imageHeight = (int)(imageWidth / aspectRatio);
    const int samplesPerPixel = 100;
    const int maxDepth = 50;

    HittableList world = basicScene();

    Point3 lookFrom(10, 2, 10);
    Point3 lookAt(0, 0, 0);
    Vec3 up(0, 1, 0);
    double distToFocus = 10.0;
    double aperture = 0.1;
    Camera cam(lookFrom, lookAt, up, 20, aspectRatio, aperture, distToFocus);

    std::cout << "P3\n" << imageWidth << " " << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; j--)
    {
        std::cerr << "\rScanlines remaining: " << j << " " << std::flush;
        for (int i = 0; i < imageWidth; i++)
        {
            Colour pixelColour(0, 0, 0);
            for (int x = 0; x < samplesPerPixel; x++)
            {
                double u = (i + RandomDouble()) / (imageWidth-1);
                double v = (j + RandomDouble()) / (imageHeight-1);
                Ray r = cam.GetRay(u, v);
                pixelColour += rayColour(r, world, maxDepth);
            }
            WriteColour(std::cout, pixelColour, samplesPerPixel);
        }
    }
    std::cerr << "\nDone\n";

    return 0;
}

Colour rayColour (const Ray& r, const Hittable& world, int depth)
{
    HitRecord rec;

    if (depth <= 0)
        return Colour(0, 0, 0);

    if (world.Hit(r, 0.001, infinity, rec))
    {
        Ray scattered;
        Colour attenuation;
        if (rec.matPtr->Scatter(r, rec, attenuation, scattered))
            return attenuation * rayColour(scattered, world, depth - 1);
        return Colour(0, 0, 0);
    }

    Vec3 unitDirection = Vec3::UnitVector(r.Direction());
    double t = 0.5 * (unitDirection.y() + 1.0);
    return (1.0 - t) * Colour(1, 1, 1) + t * Colour(0.5, 0.7, 1.0);
}

HittableList randomScene()
{
    HittableList world;

    auto groundMaterial = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -1000.0, 0), 1000, groundMaterial));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double chooseMat = RandomDouble();
            Point3 center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Point3(4, 0.2, 0)).Length() > 0.9)
            {
                std::shared_ptr<Material> sphereMaterial;

                if (chooseMat < 0.8) // Diffuse
                {
                    Colour albedo = Colour::Random() * Colour::Random();
                    sphereMaterial = std::make_shared<Lambertian>(albedo);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else if (chooseMat < 0.95) // Metal
                {
                    Vec3 albedo = Colour::Random(0.5, 1);
                    double fuzz = RandomDouble(0, 0.5);
                    sphereMaterial = std::make_shared<Metal>(albedo, fuzz);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
                else // Glass
                {
                    sphereMaterial = std::make_shared<Dielectric>(1.5);
                    world.Add(std::make_shared<Sphere>(center, 0.2, sphereMaterial));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

HittableList basicScene()
{
    HittableList world;

    auto groundMaterial = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    world.Add(std::make_shared<Sphere>(Point3(0, -1000.0, 0), 1000, groundMaterial));

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.Add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.Add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
    world.Add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}