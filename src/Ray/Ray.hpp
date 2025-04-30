/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Ray
*/

#pragma once

#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"
#include "../Interfaces/HitInfo.hpp"
#include <vector>
#include <memory>

namespace RayTracer {

    class Ray {
        public:
            Math::Point3D origin;
            Math::Vector3D direction;

            Ray() = default;
            Ray(const Math::Point3D& o, const Math::Vector3D& d) : origin(o), direction(d) {}
            HitInfo find_intersection(const std::vector<std::unique_ptr<class IPrimitive>> &primitives) const;
    };

}
