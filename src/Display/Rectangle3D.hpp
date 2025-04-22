/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Rectangle3D.hpp
*/

#pragma once

#include "../Points/Point3D.hpp"
#include "../Vectors/Vector3D.hpp"
#include <cmath>
#include <iostream>

namespace Math {
    class Rectangle3D {
        public:
            Rectangle3D(const Point3D& origin, const Vector3D& horizontal, const Vector3D& vertical);
            ~Rectangle3D() = default;

            Point3D getOrigin() const;
            Vector3D getHorizontal() const;
            Vector3D getVertical() const;
            Point3D getPointAt(double u, double v) const;

        private:
            Point3D _origin;
            Vector3D _horizontal;
            Vector3D _vertical;
    };
}

