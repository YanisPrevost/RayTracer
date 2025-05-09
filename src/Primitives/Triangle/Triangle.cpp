/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "Vector.hpp"

namespace RayTracer
{
    Triangle::Triangle()
    {
    }

    Triangle::Triangle(ArgumentMap params)
    {
        ArgumentMap vertexParam1 = params["vertex1"].as<ArgumentMap>();
        ArgumentMap vertexParam2 = params["vertex2"].as<ArgumentMap>();
        ArgumentMap vertexParam3 = params["vertex3"].as<ArgumentMap>();
        vertex1 = Math::Point3D(
            vertexParam1["x"].as<double>(),
            vertexParam1["y"].as<double>(),
            vertexParam1["z"].as<double>());
        vertex2 = Math::Point3D(
            vertexParam2["x"].as<double>(),
            vertexParam2["y"].as<double>(),
            vertexParam2["z"].as<double>());
        vertex3 = Math::Point3D(
            vertexParam3["x"].as<double>(),
            vertexParam3["y"].as<double>(),
            vertexParam3["z"].as<double>());
        _color = Math::Vector3D(params["color"].as<Math::Vector3D>());
        edge1 = vertex2 - vertex1;
        edge2 = vertex3 - vertex1;
        normal = edge1.cross(edge2).normalize();
    }

    Triangle::~Triangle()
    {
    }

    HitInfo Triangle::intersect(const Ray& ray) const
    {
        HitInfo info;
        info.hit = false;

        Math::Vector3D P = ray.direction.cross(edge2);
        auto det = edge1.dot(P);
        // if (det < 0)               // ray hitting the back side
        // return info;
        if (std::fabs(det) < 1e-8f) {
            return info;
        }
        double f = 1 / det;
        Math::Vector3D S = ray.origin - vertex1;
        double u = (S.dot(P)) * f;
        if (u < 0 || u > 1)
            return info;
        Math::Vector3D Q = S.cross(edge1);
        double v = f * (ray.direction.dot(Q));
        if (v < 0 || u + v > 1)
            return info;
        double hitDistance = f * (edge2.dot(Q));
        if (hitDistance < 1e-8f)
            return info;
        info.hit = true;
        info.color = _color;
        info.distance = hitDistance;
        info.normal = normal;
        info.point = ray.origin + ray.direction * hitDistance;
        info.reflection = 0.0;
        return info;
    }

    AABB Triangle::getBoundingBox()
    {
        if (boundingBox.has_value())
            return boundingBox.value();
        double minX = std::min(std::min(vertex1.X, vertex2.X), vertex3.X);
        double minY = std::min(std::min(vertex1.Y, vertex2.Y), vertex3.Y);
        double minZ = std::min(std::min(vertex1.Z, vertex2.Z), vertex3.Z);
        Math::Point3D minPoint(minX, minY, minZ);
        double maxX = std::max(std::max(vertex1.X, vertex2.X), vertex3.X);
        double maxY = std::max(std::max(vertex1.Y, vertex2.Y), vertex3.Y);
        double maxZ = std::max(std::max(vertex1.Z, vertex2.Z), vertex3.Z);
        Math::Point3D maxPoint(maxX, maxY, maxZ);
        boundingBox = AABB(minPoint, maxPoint);
        return (boundingBox.value());
    }

    extern "C" {
        const char *getPrimitiveName() {
            return "triangles";
        }
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap params) {
            return  std::make_unique<Triangle>(params);
        }
    }
}