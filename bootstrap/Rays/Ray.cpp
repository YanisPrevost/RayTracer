/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Ray.cpp
*/

#include "Ray.hpp"

namespace RayTracer {

    Ray::Ray(const Math::Point3D& origin, const Math::Vector3D& direction) {
        this->origin = origin;
        this->direction = direction;
    }

    const Math::Point3D& Ray::getOrigin() const {
        return origin;
    }

    const Math::Vector3D& Ray::getDirection() const {
        return direction;
    }
}