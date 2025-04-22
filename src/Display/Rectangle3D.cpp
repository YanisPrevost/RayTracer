/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Rectangle3D.cpp
*/

#include "Rectangle3D.hpp"

namespace Math {
    Rectangle3D::Rectangle3D(const Point3D& origin, const Vector3D& horizontal, const Vector3D& vertical)
    {
        _origin = origin;
        _horizontal = horizontal;
        _vertical = vertical;
    }

    Point3D Rectangle3D::getOrigin() const
    {
        return _origin;
    }

    Vector3D Rectangle3D::getHorizontal() const
    {
        return _horizontal;
    }

    Vector3D Rectangle3D::getVertical() const
    {
        return _vertical;
    }

    Point3D Rectangle3D::getPointAt(double u, double v) const
    {
        Point3D point = _origin;
        point = point + (_horizontal * u);
        point = point + (_vertical * v);
        return point;
    }
}
