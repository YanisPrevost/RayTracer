/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector3D.hpp
*/

#pragma once
#include <cmath>
#include <iostream>

namespace Math {
    class Vector3D {
        private:
            double x;
            double y;
            double z;
        public:
            Vector3D() = default;
            Vector3D(double x, double y, double z);
            double length() const;
            double dot(const Vector3D& other) const;
            Vector3D operator+(const Vector3D& other) const;
            Vector3D& operator+=(const Vector3D& other);

            Vector3D operator-(const Vector3D& other) const;
            Vector3D& operator-=(const Vector3D& other);

            Vector3D operator*(const Vector3D& other) const;
            Vector3D& operator*=(const Vector3D& other);

            Vector3D operator/(const Vector3D& other) const;
            Vector3D& operator/=(const Vector3D& other);

            Vector3D operator*(double scalar) const;
            Vector3D& operator*=(double scalar);

            Vector3D operator/(double scalar) const;
            Vector3D& operator/=(double scalar);

            // Getters : x, y, z
            double getX() const { return x; }
            double getY() const { return y; }
            double getZ() const { return z; }
        };
    Vector3D operator*(double scalar, const Vector3D& vector);
}