/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Alights
*/

#include "./ALights.hpp"
namespace RayTracer
{
    // ALights::ALights()
    // {
    // }

    ALights::~ALights()
    {
    }

    Math::Vector3D ALights::getColor() const
    {
        return _color;
    }
    double ALights::getIntensity() const
    {
        return _intensity;
    }


}