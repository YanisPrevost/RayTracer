/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Camera.cpp
*/

#include "Camera.hpp"
#include <cmath>

namespace RayTracer {

    Camera::Camera(const Math::Point3D& position, const Math::Vector3D& direction, const Math::Vector3D& up, double fov, double aspectRatio)
        : position(position), direction(direction.normalize()), up(up.normalize()), fov(fov), aspectRatio(aspectRatio)
    {
    }

    Ray Camera::generate_ray(double u, double v) const
    {
        double theta = fov * M_PI / 180.0;
        double halfHeight = tan(theta / 2);
        double halfWidth = aspectRatio * halfHeight;

        Math::Vector3D w = direction * (-1.0);
        Math::Vector3D u_vec = up.cross(w).normalize();
        Math::Vector3D v_vec = w.cross(u_vec);

        double uu = (2.0 * u - 1.0) * halfWidth;
        double vv = (2.0 * v - 1.0) * halfHeight;

        Math::Vector3D rayDir = u_vec * uu + v_vec * vv - w;
        rayDir = rayDir.normalize();

        return Ray(position, rayDir);
    }

    void Camera::lookAt(const Math::Point3D& target)
    {
        direction = Math::Vector3D(
            target.X - position.X,
            target.Y - position.Y,
            target.Z - position.Z
        ).normalize();

        Math::Vector3D right = Math::Vector3D(0, 1, 0).cross(direction).normalize();
        up = direction.cross(right).normalize();
    }

}
