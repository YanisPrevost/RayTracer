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
    class DirectionalLight : public ALights {
        public:
            DirectionalLight(
                const Math::Point3D& pos,
                const Math::Vector3D& col,
                double intensity) : ALights(pos, col, intensity) {};
            ~DirectionalLight();
            Math::Vector3D computePointLightingColor(HitInfo &info, const RayTracer &raytracer) const;
        protected:
        private:
    };
}

