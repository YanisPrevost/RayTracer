/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Sphere.hpp
*/

#pragma once

#include <cmath>
#include <iostream>
#include "../../Vectors/Vector3D.hpp"
#include "../../Points/Point3D.hpp"
#include "../../Rays/Ray.hpp"
#include "../../Interfaces/IShape.hpp"

namespace RayTracer {
    class Sphere : public IShape {
    private:
        Math::Point3D center;
        double radius;
    public:
        Sphere();
        Sphere(const Math::Point3D& center, double radius);
        bool hits(const Ray& ray) const override;
        const char* getType() const override { return "Sphere"; }
    };
}