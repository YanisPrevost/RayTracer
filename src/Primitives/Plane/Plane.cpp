/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"
#include <cmath>
#include <iostream>
#include <limits>

namespace RayTracer {

    Plane::Plane(const std::vector<double>& params) : position(0, 0, 0), normal(0, 0, 1), axis("Z"), color(255, 255, 255), reflection(0.0)
    {
        if (params.size() >= 8) {
            position = Math::Vector3D(params[0], params[1], params[2]);
            switch (static_cast<int>(params[3])) {
                case 0:
                    axis = "X";
                    break;
                case 1:
                    axis = "Y";
                    break;
                case 2:
                default:
                    axis = "Z";
                    break;
            }
            color = Math::Vector3D(params[4], params[5], params[6]);
            reflection = params[7];
            setNormal();
        }
    }

    Plane::Plane(const std::string& axis, const Math::Vector3D& position,
            const Math::Vector3D& color, double reflection) : position(position), axis(axis), color(color), reflection(reflection)
    {
        setNormal();
    }

    void Plane::setNormal()
    {
        if (axis == "X" || axis == "x")
            normal = Math::Vector3D(1, 0, 0);
        else if (axis == "Y" || axis == "y")
            normal = Math::Vector3D(0, 1, 0);
        else
            normal = Math::Vector3D(0, 0, 1);
    }

    HitInfo Plane::intersect(const Ray& ray) const
    {
        HitInfo info;
        info.hit = false;

        double denom = normal.dot(ray.direction);

        if (std::fabs(denom) < 1e-6)
            return info;
        Math::Vector3D rayToPlane = Math::Vector3D(position.X - ray.origin.X, position.Y - ray.origin.Y, position.Z - ray.origin.Z);
        double t = rayToPlane.dot(normal) / denom;
        if (t < 0)
            return info;
        info.hit = true;
        info.distance = t;
        info.point = Math::Point3D(ray.origin.X + ray.direction.X * t, ray.origin.Y + ray.direction.Y * t, ray.origin.Z + ray.direction.Z * t);
        info.normal = normal;
        if (denom > 0)
            info.normal = Math::Vector3D(-normal.X, -normal.Y, -normal.Z);
        info.color = color;
        info.reflection = reflection;
        return info;
    }

    std::string Plane::getName() const
    {
        return "Plane";
    }

    std::unique_ptr<IPrimitive> Plane::create(const std::vector<double>& params)
    {
        if (params.size() < 8)
            return nullptr;
        return std::make_unique<Plane>(params);
    }

    extern "C" {
        std::unique_ptr<IPrimitive> createPrimitive(const std::vector<double>& params) {
            return std::make_unique<Plane>(params);
        }
    }

}