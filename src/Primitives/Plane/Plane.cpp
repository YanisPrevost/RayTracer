/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

namespace RayTracer {

        Plane::Plane() : position(Math::Point3D(0, 0, 0)), axis("Z") {}
        Plane::Plane(const Math::Point3D& point, const std::string& axis) : position(point), axis(axis) {}

        bool Plane::hits(const Ray& ray) const
        {
            Math::Vector3D normal;
            normal = Math::Vector3D(0, 0, 1);

            double denominator = normal.dot(ray.getDirection());
            if (std::abs(denominator) < 1e-6)
                return false;
            Math::Vector3D rayOriginToPlane = position - ray.getOrigin();
            double t = rayOriginToPlane.dot(normal) / denominator;
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

