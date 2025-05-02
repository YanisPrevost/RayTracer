/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Plane.cpp
*/

#include "Plane.hpp"
#include <cmath>
#include <stdexcept>
#include "../../Parsing/ArgumentMap.hpp"

namespace RayTracer {

    Plane::Plane(Axis axis, double position, const Math::Vector3D& color, double reflection)
        : axis(axis), position(position), color(color), reflection(reflection) {}

    Plane::Plane(ArgumentMap map)
    {
        if (map["axis"].as<std::string>() == "Z")
            axis = Axis::Z;
        if (map["axis"].as<std::string>() == "X")
            axis = Axis::X;
        if (map["axis"].as<std::string>() == "Y")
            axis = Axis::Y;
        position = map["position"].as<int>();
        color = map["color"].as<Math::Vector3D>();
        reflection = 0.0;
    }

    Plane::Plane(const std::vector<double>& params) {
        if (params.size() >= 5) {
            axis = static_cast<Axis>(static_cast<int>(params[0]));
            position = params[1];
            color = Math::Vector3D(params[2], params[3], params[4]);
            reflection = (params.size() > 5) ? params[5] : 0.0;
        } else {
            axis = Axis::Z;
            position = 0.0;
            color = Math::Vector3D(1, 1, 1);
            reflection = 0.0;
        }
    }

    HitInfo Plane::intersect(const Ray& ray) const {
        HitInfo info;
        info.hit = false;
        double normalComponent = 0;
        Math::Vector3D normal;

        switch (axis) {
            case Axis::X:
                normal = Math::Vector3D(1, 0, 0);
                normalComponent = ray.direction.X;
                break;
            case Axis::Y:
                normal = Math::Vector3D(0, 1, 0);
                normalComponent = ray.direction.Y;
                break;
            case Axis::Z:
                normal = Math::Vector3D(0, 0, 1);
                normalComponent = ray.direction.Z;
                break;
        }

        if (std::fabs(normalComponent) < 1e-8)
            return info;

        double d = 0;
        switch (axis) {
            case Axis::X:
                d = (position - ray.origin.X) / ray.direction.X;
                break;
            case Axis::Y:
                d = (position - ray.origin.Y) / ray.direction.Y;
                break;
            case Axis::Z:
                d = (position - ray.origin.Z) / ray.direction.Z;
                break;
        }
        if (d < 0)
            return info;
        info.hit = true;
        info.distance = d;
        info.point = ray.origin + ray.direction * d;

        if (ray.direction.dot(normal) > 0)
            info.normal = normal * -1;
        else
            info.normal = normal;
        info.color = color;
        info.reflection = reflection;
        return info;
    }

    std::string Plane::getName() const {
        return "Plane";
    }

    std::unique_ptr<IPrimitive> Plane::create(const std::vector<double>& params) {
        if (params.size() >= 5) {
            Axis axis = static_cast<Axis>(static_cast<int>(params[0]));
            double position = params[1];
            Math::Vector3D color(params[2], params[3], params[4]);
            double reflection = (params.size() > 5) ? params[5] : 0.0;

            return std::make_unique<Plane>(axis, position, color, reflection);
        }

        return std::make_unique<Plane>();
    }

    Axis Plane::stringToAxis(const std::string& axisStr) {
        if (axisStr == "X" || axisStr == "x")
            return Axis::X;
        else if (axisStr == "Y" || axisStr == "y")
            return Axis::Y;
        else if (axisStr == "Z" || axisStr == "z")
            return Axis::Z;
        else
            throw std::invalid_argument("Invalid axis string: " + axisStr);
    }

    extern "C" {
        const char *getPrimitiveName() {
            return "planes";
        }
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap params) {
            return std::make_unique<Plane>(params);
        }
    }

}