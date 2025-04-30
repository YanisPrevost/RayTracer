/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#include "PointLight.hpp"
#include "../../Interfaces/ILights.hpp"
#include <unordered_map>
#include "../../Builder/RayTracer.hpp"
#include "../../Interfaces/HitInfo.hpp"
namespace RayTracer
{

    PointLight::~PointLight()
    {
    }

    Math::Vector3D PointLight::computeDiffuseLightingColor(HitInfo &info, const RayTracer &raytracer) const
    {
        Math::Vector3D lightDir = getPosition() - info.point;

        Ray ray(info.point, lightDir);
        HitInfo closestHit = ray.find_intersection(raytracer.getPrimitives());
        if (closestHit.hit) {
            Math::Vector3D shadowColor = info.color *= 0.1;
            return shadowColor;
        }
        lightDir = lightDir.normalize();
        double diffuse = std::max(info.normal.dot(lightDir), 0.0);
        diffuse *= _intensity;
        diffuse = std::max(diffuse, 0.1);
        Math::Vector3D color =  (info.color * diffuse) * this->_color;
        return color;
    }
}

extern "C" {
    std::unique_ptr<RayTracer::ILights> createLight(
        const Math::Point3D& pos,
        const Math::Vector3D& col,
        double intensity,
        std::unordered_map<std::string, std::string> &)
    {
        return  std::make_unique<RayTracer::PointLight>(pos, col, intensity);
    }
}
