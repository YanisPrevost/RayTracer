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
#include "../../Parsing/ArgumentMap.hpp"
#include "../../Interfaces/HitInfo.hpp"
namespace RayTracer
{

    PointLight::~PointLight()
    {
    }

    Math::Vector3D PointLight::computeLightingColor(HitInfo &info, const RayTracer &raytracer) const
    {
        Math::Vector3D lightDir = position - info.point;

        double distance = lightDir.length();
        lightDir = lightDir.normalize();
        const double bias = 1e-4;
        Ray ray(info.point + info.normal * bias, lightDir);
        HitInfo closestHit = ray.find_intersection(raytracer.getPrimitives());
        if (closestHit.hit && closestHit.distance < distance) {
            Math::Vector3D shadowColor(0, 0, 0);
            return shadowColor;
        }
        double diffuse = std::max(info.normal.dot(lightDir), 0.0);
        diffuse *= _intensity;
        double attenuation = 1.0 / (1.0 + 0.09 * distance + 0.032 * distance * distance);;
        diffuse *= attenuation;
        Math::Vector3D color =  (info.color * diffuse) * this->_color;
        return color;
    }
}

extern "C" {
    const char *getLightName() {
        return "point";
    }
    std::unique_ptr<RayTracer::ILights> createLight(RayTracer::ArgumentMap params)
    {
        return  std::make_unique<RayTracer::PointLight>(params);
    }
}
