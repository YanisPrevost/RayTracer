/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Camera.cpp
*/

#include "Camera.hpp"
#include <cmath>

namespace RayTracer {

    Camera::Camera(const Math::Point3D& position, double fieldOfView, int width, int height)
        : origin(position), screen(position, Math::Vector3D(0, 0, 0), Math::Vector3D(0, 0, 0))
    {
        double focalDistance = 1.0;
        double fovRadians = fieldOfView * M_PI / 180.0;
        double screenHeight = 2 * tan(fovRadians / 2);
        double aspectRatio = static_cast<double>(width) / static_cast<double>(height);
        double screenWidth = screenHeight * aspectRatio;

        Math::Point3D screenOrigin(
            position.getX() - screenWidth / 2,
            position.getY() + focalDistance,
            position.getZ() - screenHeight / 2
        );
        screen = Math::Rectangle3D(
            screenOrigin,
            Math::Vector3D(screenWidth, 0, 0),
            Math::Vector3D(0, 0, screenHeight)
        );
    }

    Ray Camera::ray(double u, double v) const
    {
        Math::Point3D pointOnScreen = screen.getPointAt(u, v);
        Math::Vector3D direction = pointOnScreen - origin;
        return Ray(origin, direction);
    }
}