/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Cylinder.cpp
*/

#include "Cylinder.hpp"
#include <cmath>
#include <algorithm>
#include <iostream>

namespace RayTracer {

    Cylinder::Cylinder(const Math::Point3D& position, double radius, double height,
        const Math::Vector3D& direction, const Math::Vector3D& color, double reflection)
        : position(position), radius(radius), height(height),
        direction(direction.normalize()), color(color), reflection(reflection) {}

    Cylinder::Cylinder(const std::vector<double>& params) {
        position = Math::Point3D(params[0], params[1], params[2]);
        radius = params[3];
        height = params[4];
        direction = Math::Vector3D(params[5], params[6], params[7]).normalize();
        color = Math::Vector3D(params[8], params[9], params[10]);
        reflection = params[11];
    }

    Cylinder::Cylinder(ArgumentMap params)
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

    HitInfo Cylinder::intersect(const Ray& ray) const
    {
        HitInfo info;
        info.hit = false;
        info.color = color;
        info.reflection = reflection;

        const Math::Vector3D cylinderAxis = direction.normalize();
        Math::Vector3D oc = ray.origin - position;
        double a = ray.direction.dot(ray.direction) - std::pow(ray.direction.dot(cylinderAxis), 2);
        double b = 2.0 * (oc.dot(ray.direction) - (oc.dot(cylinderAxis) * ray.direction.dot(cylinderAxis)));
        double c = oc.dot(oc) - std::pow(oc.dot(cylinderAxis), 2) - radius * radius;
        double discriminant = b * b - 4 * a * c;
        if (discriminant < 0)
            return info;
        double t1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + std::sqrt(discriminant)) / (2.0 * a);
        if (t1 < 0 && t2 < 0)
            return info;
        double t = (t1 < 0) ? t2 : ((t2 < 0) ? t1 : std::min(t1, t2));
        Math::Point3D intersectionPoint = ray.origin + ray.direction * t;
        double projectionOnAxis = (intersectionPoint - position).dot(cylinderAxis);
        if (projectionOnAxis < 0 || projectionOnAxis > height) {
            double tBottom = -oc.dot(cylinderAxis) / ray.direction.dot(cylinderAxis);
            if (tBottom > 0) {
                Math::Point3D bottomHit = ray.origin + ray.direction * tBottom;
                Math::Vector3D hitOffset = bottomHit - position;
                if (hitOffset.dot(hitOffset) - std::pow(hitOffset.dot(cylinderAxis), 2) <= radius * radius) {
                    info.hit = true;
                    info.distance = tBottom;
                    info.point = bottomHit;
                    info.normal = cylinderAxis * (-1.0);
                    return info;
                }
            }
            Math::Point3D topCenter = position + cylinderAxis * height;
            Math::Vector3D oc_top = ray.origin - topCenter;
            double tTop = -oc_top.dot(cylinderAxis) / ray.direction.dot(cylinderAxis);
            if (tTop > 0) {
                Math::Point3D topHit = ray.origin + ray.direction * tTop;
                Math::Vector3D hitOffset = topHit - topCenter;
                if (hitOffset.dot(hitOffset) - std::pow(hitOffset.dot(cylinderAxis), 2) <= radius * radius) {
                    info.hit = true;
                    info.distance = tTop;
                    info.point = topHit;
                    info.normal = cylinderAxis;
                    return info;
                }
            }
            return info;
        }
        info.hit = true;
        info.distance = t;
        info.point = intersectionPoint;
        Math::Vector3D projectionOnAxisVector = cylinderAxis * projectionOnAxis;
        Math::Vector3D centerToIntersect = intersectionPoint - (position + projectionOnAxisVector);
        info.normal = centerToIntersect.normalize();
        return info;
    }

    std::string Cylinder::getName() const
    {
        return "cylinder";
    }

    std::unique_ptr<IPrimitive> Cylinder::create(const std::vector<double>& params)
    {
        return std::make_unique<Cylinder>(params);
    }

    extern "C" {
        const char *getPrimitiveName() {
            return "cylinders";
        }
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap params) {
            return std::make_unique<Cylinder>(params);
        }
    }

}