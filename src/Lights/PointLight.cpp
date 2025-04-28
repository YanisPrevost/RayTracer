/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"
namespace RayTracer
{
// PointLight::PointLight()
// {
// }

PointLight::~PointLight()
{
}

double PointLight::getDiffuse(HitInfo &info) const
{
    Math::Vector3D lightDir = getPosition() - info.point;

    lightDir /= lightDir.length();
    double diffuse = info.normal.dot(lightDir);
    return diffuse;
}
}