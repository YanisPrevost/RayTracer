/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"

namespace RayTracer {
    Camera::Camera() : origin(Math::Point3D(0, 0, -5)), screen(Math::Point3D(0, 0, -3), Math::Vector3D(2, 0, 0), Math::Vector3D(0, 2, 0)) {}
    Camera::Camera(const Math::Point3D& origin, const Math::Rectangle3D& screen) : origin(origin), screen(screen) {}

    Ray Camera::ray(double u, double v) const
    {
        Math::Point3D pointOnScreen = screen.getPointAt(u, v);
        Math::Vector3D direction = pointOnScreen - origin;
        return Ray(origin, direction);
    }
}
