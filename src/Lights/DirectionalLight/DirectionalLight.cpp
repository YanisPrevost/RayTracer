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
#include "../Ray/Ray.hpp"

namespace RayTracer {

    DirectionalLight::DirectionalLight(ArgumentMap params) : ALights(params["color"].as<Color>(), params["intensity"].as<double>())
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

    Color DirectionalLight::computeLightingColor(HitInfo &info, const Scene &scene) const
    {
        Math::Vector3D lightDir = _direction;

        Ray ray(info.getPoint(), lightDir);
        auto hits = ray.find_intersection(scene.getPrimitives(), scene.getTree());
        if (hits.size() > 0) {
            Color shadowColor(0, 0, 0);
            return shadowColor;
        }
        lightDir = lightDir.normalize();
        double diffuse = std::max(info.getNormal().dot(lightDir), 0.0);
        diffuse *= _intensity;
        // Color color = info.color * this->_color * diffuse;
        double shininess = info.getMaterial().getShininess();
        Math::Vector3D N = info.getNormal().normalize();
        Math::Vector3D L = lightDir.normalize();
        Math::Vector3D V = (info.getOriginDirection()).normalize();
        Math::Vector3D reflectedLightDir = ((N *  ((N.dot( L) * 2) )) - L).normalize();
        Color specularColor = info.getColor() * (_intensity * pow(std::max(reflectedLightDir.dot(V), 0.0), shininess));
        Color color =  ((info.getColor() * diffuse) * this->_color) + specularColor;
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