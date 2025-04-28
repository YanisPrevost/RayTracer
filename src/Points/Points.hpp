/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Points.hpp
*/
#pragma once

#include <cmath>
#include "../Vectors/Vector.hpp"


namespace Math {

    class Point3D {
        public:
            double X;
            double Y;
            double Z;

            Point3D() : X(0), Y(0), Z(0) {}
            Point3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

            Point3D operator+(const Vector3D& vec) const;
            Point3D& operator+=(const Vector3D& vec);
            Vector3D operator-(const Point3D& other) const;
    };
}