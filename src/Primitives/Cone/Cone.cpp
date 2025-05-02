/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Cone.cpp
*/

#include "Cone.hpp"
#include <cmath>

namespace RayTracer {

    Cone::Cone(const Math::Point3D& position, double radius, double height,
               const Math::Vector3D& direction, const Math::Vector3D& color, double reflection)
        : position(position), radius(radius), height(height),
          direction(direction.normalize()), color(color), reflection(reflection) {}

    Cone::Cone(const std::vector<double>& params) {
        position = Math::Point3D(params[0], params[1], params[2]);
        radius = params[3];
        height = params[4];
        direction = Math::Vector3D(params[5], params[6], params[7]).normalize();
        color = Math::Vector3D(params[8], params[9], params[10]);
        reflection = params[11];
    }

    Cone::Cone(ArgumentMap params)
    {
        ArgumentMap pos = params["position"].as<ArgumentMap>();
        position = Math::Point3D(pos["x"].as<double>(), pos["y"].as<double>(), pos["z"].as<double>());
        radius = params["radius"].as<double>();
        height = params["height"].as<double>();
        ArgumentMap directionMap = params["direction"].as<ArgumentMap>();
        direction = Math::Vector3D(directionMap["x"].as<int>(), directionMap["y"].as<int>(), directionMap["z"].as<int>());
        color = params["color"].as<Math::Vector3D>();
        reflection = 0;
    }

    HitInfo Cone::intersect(const Ray& ray) const
    {
        HitInfo info;
        info.hit = false;

        Math::Vector3D axis = direction.normalize();
        Math::Vector3D oc = ray.origin - position;

        double tanTheta = radius / height;
        double tanTheta2 = tanTheta * tanTheta;
        double a = ray.direction.dot(ray.direction) - (1 + tanTheta2) * pow(ray.direction.dot(axis), 2);
        double b = 2 * (oc.dot(ray.direction) - (1 + tanTheta2) * (oc.dot(axis)) * (ray.direction.dot(axis)));
        double c = oc.dot(oc) - (1 + tanTheta2) * pow(oc.dot(axis), 2);
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return info;
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);
        double t = (t1 > 0) ? t1 : t2;
        if (t < 0)
            return info;
        Math::Point3D hitPoint = ray.origin + ray.direction * t;
        Math::Vector3D ap = hitPoint - position;
        double heightOnCone = ap.dot(axis);
        if (heightOnCone < 0 || heightOnCone > height)
            return info;
        info.hit = true;
        info.distance = t;
        info.point = hitPoint;
        Math::Vector3D s = hitPoint - (position + axis * heightOnCone);
        Math::Vector3D normal = (s - axis * s.dot(axis) / axis.dot(axis)).normalize();
        info.normal = normal;
        info.color = color;
        info.reflection = reflection;
        return info;
    }

    std::string Cone::getName() const
    {
        return "Cone";
    }

    std::unique_ptr<IPrimitive> Cone::create(const std::vector<double>& params)
    {
        if (params.size() >= 11) {
            Math::Point3D position(params[0], params[1], params[2]);
            double radius = params[3];
            double height = params[4];
            Math::Vector3D direction(params[5], params[6], params[7]);
            Math::Vector3D color(params[8], params[9], params[10]);
            double reflection = (params.size() > 11) ? params[11] : 0.0;
            return std::make_unique<Cone>(position, radius, height, direction, color, reflection);
        }
        return std::make_unique<Cone>(params);
    }

    extern "C" {
        const char *getPrimitiveName() {
            return "cones";
        }
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap params) {
            return std::make_unique<Cone>(params);
        }
    }

}