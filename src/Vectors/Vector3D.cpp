/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Vector3D.cpp
*/

#include "Vector3D.hpp"

namespace Math {

    Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

    double Vector3D::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    double Vector3D::dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D Vector3D::operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D& Vector3D::operator+=(const Vector3D& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    Vector3D Vector3D::operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D& Vector3D::operator-=(const Vector3D& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*(const Vector3D& other) const {
        return Vector3D(x * other.x, y * other.y, z * other.z);
    }

    Vector3D& Vector3D::operator*=(const Vector3D& other) {
        x *= other.x;
        y *= other.y;
        z *= other.z;
        return *this;
    }

    Vector3D Vector3D::operator/(const Vector3D& other) const {
        return Vector3D(x / other.x, y / other.y, z / other.z);
    }

    Vector3D& Vector3D::operator/=(const Vector3D& other) {
        x /= other.x;
        y /= other.y;
        z /= other.z;
        return *this;
    }

    Vector3D Vector3D::operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    Vector3D& Vector3D::operator*=(double scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }

    Vector3D Vector3D::operator/(double scalar) const {
        return Vector3D(x / scalar, y / scalar, z / scalar);
    }

    Vector3D& Vector3D::operator/=(double scalar) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vector3D operator*(double scalar, const Vector3D& vector) {
        return vector * scalar;
    }
    
    Vector3D Vector3D::normalize() const {
        double len = length();
        if (len > 0) {
            return Vector3D(x / len, y / len, z / len);
        }
        return Vector3D(0, 0, 0);
    }
    
    Vector3D Vector3D::cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }
}