/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#pragma once

#include "../../Vectors/Vector.hpp"
#include "../../Points/Points.hpp"
#include "../ALights.hpp"
#include "../../Interfaces/IPrimitive.hpp"
#include "../../Builder/RayTracer.hpp"
namespace RayTracer
{
    class PointLight : public ALights {
        public:
            PointLight(const Math::Point3D& pos, const Math::Vector3D& col, double intensity) : ALights(col, intensity) {};
            PointLight(ArgumentMap params) : ALights(params["color"].as<Math::Vector3D>(), params["intensity"].as<double>()), position(Math::Point3D(
                params["position"].as<ArgumentMap>()["x"].as<int>(),
                params["position"].as<ArgumentMap>()["y"].as<int>(),
                params["position"].as<ArgumentMap>()["z"].as<int>())) {}
            ~PointLight();
            Math::Vector3D computeLightingColor(HitInfo &info, const RayTracer &raytracer) const;
        private:
            Math::Point3D position;
    };
}

