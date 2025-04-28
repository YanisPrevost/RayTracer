/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Vector.cpp
*/

#include "Vector.hpp"

namespace Math {

    Vector3D::Vector3D() : X(0), Y(0), Z(0) {}

    Vector3D::Vector3D(double x, double y, double z) : X(x), Y(y), Z(z) {}

    double Vector3D::length() const {
        return std::sqrt(X * X + Y * Y + Z * Z);
    }

    Vector3D Vector3D::normalize() const {
        double len = length();
        if (len > 0) {
            return Vector3D(X / len, Y / len, Z / len);
        }
        return *this;
    }

    double Vector3D::dot(const Vector3D& other) const {
        return X * other.X + Y * other.Y + Z * other.Z;
    }

    Vector3D Vector3D::operator+(const Vector3D& other) const {
        return Vector3D(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3D& Vector3D::operator+=(const Vector3D& other) {
        X += other.X;
        Y += other.Y;
        Z += other.Z;
        return *this;
    }

    Vector3D Vector3D::operator-(const Vector3D& other) const {
        return Vector3D(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other) {
        X -= other.X;
        Y -= other.Y;
        Z -= other.Z;
        return *this;
    }

    Vector3D Vector3D::operator*(const Vector3D& other) const {
        return Vector3D(X * other.X, Y * other.Y, Z * other.Z);
    }

    Vector3D& Vector3D::operator*=(const Vector3D& other) {
        X *= other.X;
        Y *= other.Y;
        Z *= other.Z;
        return *this;
    }

    Vector3D Vector3D::operator/(const Vector3D& other) const {
        return Vector3D(X / other.X, Y / other.Y, Z / other.Z);
    }

    Vector3D& Vector3D::operator/=(const Vector3D& other) {
        X /= other.X;
        Y /= other.Y;
        Z /= other.Z;
        return *this;
    }

    Vector3D Vector3D::operator*(double scalar) const {
        return Vector3D(X * scalar, Y * scalar, Z * scalar);
    }

    Vector3D& Vector3D::operator*=(double scalar) {
        X *= scalar;
        Y *= scalar;
        Z *= scalar;
        return *this;
    }

    Vector3D Vector3D::operator/(double scalar) const {
        return Vector3D(X / scalar, Y / scalar, Z / scalar);
    }

    Vector3D& Vector3D::operator/=(double scalar) {
        X /= scalar;
        Y /= scalar;
        Z /= scalar;
        return *this;
    }

    Vector3D Vector3D::cross(const Vector3D& other) const {
        return Vector3D(
            Y * other.Z - Z * other.Y,
            Z * other.X - X * other.Z,
            X * other.Y - Y * other.X
        );
    }

}