/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle
*/

#include "Triangle.hpp"
#include "Vector.hpp"

RayTracer::Triangle::Triangle()
{
}

RayTracer::Triangle::~Triangle()
{
}

RayTracer::HitInfo RayTracer::Triangle::intersect(const RayTracer::Ray& ray) const
{
    HitInfo info;
    Math::Vector3D edge1 = vertex1 - vertex2;
    Math::Vector3D edge2 = vertex3 - vertex2;
    Math::Vector3D P = ray.direction.cross(edge2);
    auto det = edge1.dot(P);
    if (abs(det) < 1e-8f)
        info.hit = true;
}
