/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Point3D.cpp
*/

#include "Point3D.hpp"

namespace Math {

    Point3D::Point3D(double x, double y, double z) : x(x), y(y), z(z) {}

    Point3D Point3D::operator+(const Vector3D& vector) const {
        return Point3D(x + vector.getX(), y + vector.getY(), z + vector.getZ());
    }

    Point3D& Point3D::operator+=(const Vector3D& vector) {
        x += vector.getX();
        y += vector.getY();
        z += vector.getZ();
        return *this;
    }

    Point3D Point3D::operator-(const Vector3D& vector) const {
        return Point3D(x - vector.getX(), y - vector.getY(), z - vector.getZ());
    }

    Point3D& Point3D::operator-=(const Vector3D& vector) {
        x -= vector.getX();
        y -= vector.getY();
        z -= vector.getZ();
        return *this;
    }

    //return a vector
    Vector3D Point3D::operator-(const Point3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }
}