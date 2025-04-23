/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Camera.hpp
*/

#pragma once

#include "../Points/Point3D.hpp"
#include "../Rays/Ray.hpp"
#include "../Display/Rectangle3D.hpp"

namespace RayTracer {
    class Camera {
        private:
            Math::Point3D origin;
            Math::Rectangle3D screen;
        public:
            Camera(const Camera& other) = default;
            Camera& operator=(const Camera& other) = default;
            ~Camera() = default;
            Camera(const Math::Point3D& position, double fieldOfView, int width, int height);
            Ray ray(double u, double v) const;
    };
}
