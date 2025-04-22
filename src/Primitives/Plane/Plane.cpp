/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

namespace RayTracer {

    Plane::Plane() : point(Math::Point3D(0, 0, 0)), normal(Math::Vector3D(0, 1, 0)) {}
    Plane::Plane(const Math::Point3D& point, const Math::Vector3D& normal) : point(point), normal(normal) {}

    bool Plane::hits(const Ray& ray) const
    {
        double denominator = normal.dot(ray.getDirection());
        if (std::abs(denominator) < 1e-6) {
            return false;
        }
        double t = (point - ray.getOrigin()).dot(normal) / denominator;
        return t >= 0;
    }
}

extern "C" {
    RayTracer::IShape* create_shape() {
        return new RayTracer::Plane();
    }
    void destroy_shape(RayTracer::IShape* shape) {
        delete shape;
    }
}