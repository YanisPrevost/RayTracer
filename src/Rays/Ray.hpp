/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Ray.hpp
*/

#pragma once
#include "../Vectors/Vector3D.hpp"
#include "../Points/Point3D.hpp"

namespace RayTracer {
    class Ray {
        private:
            Math::Point3D origin;
            Math::Vector3D direction;
        public:
            Ray() = default;
            Ray(const Math::Point3D& origin, const Math::Vector3D& direction);

            const Math::Point3D& getOrigin() const { return origin; }
            const Math::Vector3D& getDirection() const { return direction; }
    };
}