/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Sphere.cpp
*/

#include "Sphere.hpp"

namespace RayTracer {

    Sphere::Sphere() : center(Math::Point3D(0, 0, 0)), radius(1.0) {}
    Sphere::Sphere(const Math::Point3D& center, double radius) : center(center), radius(radius) {}

    bool Sphere::hits(const Ray& ray) const
    {
        Math::Vector3D originToCenter = ray.getOrigin() - center;
        double a = ray.getDirection().dot(ray.getDirection()); // D · D
        double b = 2.0 * ray.getDirection().dot(originToCenter); // 2 * D · (O-C)
        double c = originToCenter.dot(originToCenter) - radius * radius; // (O-C) · (O-C) - R²
        double discriminant = b * b - 4 * a * c;
        return discriminant >= 0;
    }
}

extern "C" {

    RayTracer::IShape* create_shape() {
        return new RayTracer::Sphere();
    }
    void destroy_shape(RayTracer::IShape* shape) {
        delete shape;
    }

}