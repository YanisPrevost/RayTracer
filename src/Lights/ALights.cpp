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

    Math::Point3D ALights::getPosition() const
    {
        return _position;
    }
    Math::Vector3D ALights::getColor() const
    {
        return _color;
    }
    double ALights::getIntensity() const
    {
        return _intensity;
    }

    HitInfo Ray::find_intersection(const std::vector<std::unique_ptr<IPrimitive>> &primitives) const
    {
        HitInfo closestHit;
        closestHit.hit = false;
        closestHit.distance = std::numeric_limits<double>::max();
        for (const auto& element : primitives) {
            HitInfo hitInfo = element->intersect(*this);
            if (hitInfo.hit && hitInfo.distance < closestHit.distance && hitInfo.distance > 1e-6) {
                closestHit = hitInfo;
            }
        }
        return closestHit;
    }
}