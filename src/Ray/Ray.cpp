/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Ray
*/

#include "Ray.hpp"
#include "../Interfaces/HitInfo.hpp"
#include "../Interfaces/IPrimitive.hpp"

// Ray::Ray()
// {
// }

// Ray::~Ray()
// {
// }

RayTracer::HitInfo RayTracer::Ray::find_intersection(const std::vector<std::unique_ptr<IPrimitive>> &primitives) const
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
