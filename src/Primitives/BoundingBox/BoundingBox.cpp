/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** BoundingBox
*/

#include "BoundingBox.hpp"
#include "ArgumentMap.hpp"
#include "Points.hpp"


RayTracer::BoundingBox::BoundingBox()
{
}

RayTracer::BoundingBox::BoundingBox(RayTracer::ArgumentMap params)
{
    ArgumentMap minParam = params["min"].as<ArgumentMap>();
    auto min = Math::Point3D(
        minParam["x"].as<double>(),
        minParam["y"].as<double>(),
        minParam["z"].as<double>()
    );
    ArgumentMap maxParam = params["max"].as<ArgumentMap>();
    auto max = Math::Point3D(
        maxParam["x"].as<double>(),
        maxParam["y"].as<double>(),
        maxParam["z"].as<double>()
    );
}

RayTracer::BoundingBox::~BoundingBox()
{
}

RayTracer::HitInfo RayTracer::BoundingBox::intersect(const Ray& ray) const
{
    HitInfo hitinfo = axisAlignedBoundingBox.getHitInfo(ray);

    hitinfo.color = Math::Vector3D(0.0, 1.0, 1.0);
    return hitinfo;
}

extern "C" {
    const char *getPrimitiveName()
    {
        return "boundingboxes";
    }
    std::unique_ptr<RayTracer::IPrimitive> createPrimitive(RayTracer::ArgumentMap params)
    {
        return std::make_unique<RayTracer::BoundingBox>(params);
    }
}
