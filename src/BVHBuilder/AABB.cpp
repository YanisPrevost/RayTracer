/*
** EPITECH PROJECT, 2025
** $
** File description:
** AABB
*/

#include "AABB.hpp"
#include "../Ray/Ray.hpp"

namespace RayTracer {

    AABB::AABB() : _min(0, 0, 0), _max(0, 0, 0) {}

    AABB::~AABB() {}

    std::pair<double, double> AABB::calculateEntryPoint(const Ray& ray) const
    {
        double tx1  = (_min.X - ray.origin.X) / ray.direction.X;
        double tx2 = (_max.X - ray.origin.X) / ray.direction.X;
        double tminX = std::min(tx1, tx2);
        double tmaxX = std::max(tx1, tx2);

        double ty1  = (_min.Y - ray.origin.Y) / ray.direction.Y;
        double ty2 = (_max.Y - ray.origin.Y) / ray.direction.Y;
        double tminY = std::min(ty1, ty2);
        double tmaxY = std::max(ty1, ty2);

        double tz1  = (_min.Z - ray.origin.Z) / ray.direction.Z;
        double tz2 = (_max.Z - ray.origin.Z) / ray.direction.Z;
        double tminZ = std::min(tz1, tz2);
        double tmaxZ = std::max(tz1, tz2);

        double entryPoint = std::max(std::max(tminX, tminY), tminZ);
        double exitPoint  = std::min(std::min(tmaxX, tmaxY), tmaxZ);
        return (std::pair(entryPoint, exitPoint));
    }

    HitInfo AABB::getHitInfo(const Ray& ray) const
    {
        HitInfo hitInfo;
        double tx1  = (_min.X - ray.origin.X) / ray.direction.X;
        double tx2 = (_max.X - ray.origin.X) / ray.direction.X;
        double tminX = std::min(tx1, tx2);
        double tmaxX = std::max(tx1, tx2);

        double ty1  = (_min.Y - ray.origin.Y) / ray.direction.Y;
        double ty2 = (_max.Y - ray.origin.Y) / ray.direction.Y;
        double tminY = std::min(ty1, ty2);
        double tmaxY = std::max(ty1, ty2);

        double tz1  = (_min.Z - ray.origin.Z) / ray.direction.Z;
        double tz2 = (_max.Z - ray.origin.Z) / ray.direction.Z;
        double tminZ = std::min(tz1, tz2);
        double tmaxZ = std::max(tz1, tz2);

        double entryPoint = std::max(std::max(tminX, tminY), tminZ);
        double exitPoint  = std::min(std::min(tmaxX, tmaxY), tmaxZ);

        if (entryPoint > exitPoint || exitPoint < 0)
            return hitInfo;
        Math::Vector3D normal(1.0, 0.0, 0.0);
        if (entryPoint == tminX) {
            if ((ray.direction.X < 0))
                normal.X = 1.0;
            else
                normal.X = -1.0;
        } else if (entryPoint == tminY) {
            if ((ray.direction.Y < 0))
                normal.Y = 1.0;
            else
                normal.Y = -1.0;
        } else if (entryPoint == tminZ) {
            if ((ray.direction.Z < 0))
                normal.Z = 1.0;
            else
                normal.Z = -1.0;
        }
        hitInfo.normal = normal;
        hitInfo.hit = true;
        hitInfo.distance = entryPoint;
        return hitInfo;
    }
}