/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Point3D.hpp
*/

#pragma once
#include <cmath>
#include <iostream>
#include "../Vectors/Vector3D.hpp"

namespace Math {
    class Point3D {
    private:
        double x;
        double y;
        double z;
    public:
        Point3D() = default;
        Point3D(double x, double y, double z);

        double getX() const { return x; }
        double getY() const { return y; }
        double getZ() const { return z; }

        Point3D operator+(const Vector3D& vector) const;
        Point3D& operator+=(const Vector3D& vector);

        Point3D operator-(const Vector3D& vector) const;
        Point3D& operator-=(const Vector3D& vector);

        Vector3D operator-(const Point3D& other) const;
    };
}

