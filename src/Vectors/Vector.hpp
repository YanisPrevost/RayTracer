/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Vector.hpp
*/

#pragma once

#include <cmath>

namespace Math {
    class Vector3D {
    public:
        double X;
        double Y;
        double Z;

        Vector3D();
        Vector3D(double x, double y, double z);

        double length() const;
        Vector3D normalize() const;
        double dot(const Vector3D& other) const;

        Vector3D operator+(const Vector3D& other) const;
        Vector3D& operator+=(const Vector3D& other);
        Vector3D operator-(const Vector3D& other) const;
        Vector3D& operator-=(const Vector3D& other);
        Vector3D operator*(const Vector3D& other) const;
        Vector3D& operator*=(const Vector3D& other);
        Vector3D operator/(const Vector3D& other) const;
        Vector3D& operator/=(const Vector3D& other);

        // Opérateurs avec scalaire
        Vector3D operator*(double scalar) const;
        Vector3D& operator*=(double scalar);
        Vector3D operator/(double scalar) const;
        Vector3D& operator/=(double scalar);

        // Produit vectoriel
        Vector3D cross(const Vector3D& other) const;
    };
}
