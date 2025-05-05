/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Camera.hpp
*/

#pragma once

#include "Vector.hpp"
#include "Points.hpp"
#include "../Rectangle3D/Screen.hpp"
#include "IPrimitive.hpp"
#include "../Parsing/ArgumentMap.hpp"

namespace RayTracer {

class Camera {
    private:
        Math::Point3D position;
        Math::Vector3D direction;
        Math::Vector3D up;
        double fov;
        double aspectRatio;

    public:
        Camera(const Math::Point3D& position = Math::Point3D(0, 0, 0),
            const Math::Vector3D& direction = Math::Vector3D(0, 0, -1),
            const Math::Vector3D& up = Math::Vector3D(0, 1, 0),
            double fov = 90.0,
            double aspectRatio = 16.0/9.0);
        
        Camera(ArgumentMap params);

        Ray generate_ray(double u, double v) const;

        void lookAt(const Math::Point3D& target);

        Math::Point3D getPosition() const { return position; }
        Math::Vector3D getDirection() const { return direction; }
        Math::Vector3D getUp() const { return up; }
        double getFov() const { return fov; }
        double getAspectRatio() const { return aspectRatio; }

        void setPosition(const Math::Point3D& pos) { position = pos; }
        void setDirection(const Math::Vector3D& dir) { direction = dir.normalize(); }
        void setUp(const Math::Vector3D& up) { this->up = up.normalize(); }
        void setFov(double fov) { this->fov = fov; }
        void setAspectRatio(double ratio) { aspectRatio = ratio; }
    };
}
