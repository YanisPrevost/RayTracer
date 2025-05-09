/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#include "DirectionalLight.hpp"
#include "../../Interfaces/ILights.hpp"
#include <unordered_map>
#include "../../Builder/RayTracer.hpp"
#include "../../Interfaces/HitInfo.hpp"
#include "../../Parsing/ArgumentMap.hpp"
namespace RayTracer
{

    DirectionalLight::DirectionalLight(ArgumentMap params) : ALights(params["color"].as<Math::Vector3D>(), params["intensity"].as<double>())
    {
        _direction = Math::Vector3D(
            params["direction"].as<ArgumentMap>()["x"].as<int>(),
            params["direction"].as<ArgumentMap>()["y"].as<int>(),
            params["direction"].as<ArgumentMap>()["z"].as<int>()
        );
    }

    DirectionalLight::~DirectionalLight()
    {
    }

    Math::Vector3D DirectionalLight::computeLightingColor(HitInfo &info, const RayCaster &raytracer) const
    {
        Math::Vector3D lightDir = _direction;

        Ray ray(info.point, lightDir);
        HitInfo closestHit = ray.find_intersection(raytracer.getPrimitives());
        if (closestHit.hit) {
            Math::Vector3D shadowColor(0, 0, 0);
            return shadowColor;
        }
        lightDir = lightDir.normalize();
        double diffuse = std::max(info.normal.dot(lightDir), 0.0);
        diffuse *= _intensity;
        Math::Vector3D color =  info.color * this->_color * diffuse;
        return color;
    }

    extern "C" {
        const char *getLightName() {
            return "directional";
        }
        std::unique_ptr<ILights> createLight(ArgumentMap params)
        {
            return  std::make_unique<DirectionalLight>(params);
        }
    }

}