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
namespace RayTracer
{

    PointLight::~PointLight()
    {
    }

    Math::Vector3D PointLight::computeDiffuseLightingColor(HitInfo &info, const RayTracer &raytracer) const
    {
        Math::Vector3D lightDir = getPosition() - info.point;

        Ray ray(info.point, lightDir);
        HitInfo closestHit = raytracer.find_intersection(ray);
        if (closestHit.hit&& closestHit.distance > 0.001) {
            std::cout << "Hit detected while going to light source at distance: " << closestHit.distance << std::endl;
            return Math::Vector3D(0, 0, 0);
        }
        lightDir = lightDir.normalize();
        double diffuse = std::max(info.normal.dot(lightDir), 0.0);
        diffuse *= _intensity;
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
