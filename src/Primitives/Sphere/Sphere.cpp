/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"
#include <cmath>

namespace RayTracer {

    Sphere::Sphere(const Math::Point3D& center, double radius, const Math::Vector3D& color, double reflection)
        : center(center), radius(radius), color(color), reflection(reflection) {}
    Sphere::Sphere(const std::vector<double>& params) :
    center(params[0], params[1], params[2]),
    radius(params[3]),
    color(params[4], params[5], params[6]), reflection(reflection) {
        double reflection = (params.size() > 7) ? params[7] : 0.0;
    }

    HitInfo Sphere::intersect(const Ray& ray) const
    {
        HitInfo info;
        info.hit = false;
        Math::Vector3D oc = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double b = 2.0 * oc.dot(ray.direction);
        double c = oc.dot(oc) - radius * radius;

        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return info;

        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);
        double t = (t1 > 0) ? t1 : t2;
        if (t < 0)
            return info;
        info.hit = true;
        info.distance = t;
        info.point = ray.origin + ray.direction * t;
        info.normal = (info.point - center).normalize();
        info.color = color;
        info.reflection = reflection;
        return info;
    }

    std::string Sphere::getName() const
    {
        return "Sphere";
    }

    // std::unique_ptr<IPrimitive> Sphere::create(const std::vector<double>& params)
    // {
    //     if (params.size() >= 7) {
    //         Math::Point3D center(params[0], params[1], params[2]);
    //         double radius = params[3];
    //         Math::Vector3D color(params[4], params[5], params[6]);
    //         double reflection = (params.size() > 7) ? params[7] : 0.0;

    //         return std::make_unique<Sphere>(center, radius, color, reflection);
    //     }

    //     return std::make_unique<Sphere>();
    // }

    extern "C" {
        std::unique_ptr<IPrimitive> createPrimitive(const std::vector<double>& params) {
            return  std::make_unique<Sphere>(params);
        }
    }

}
