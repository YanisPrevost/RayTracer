/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILights.hpp
*/

#pragma once
#include <memory>
#include "Vector.hpp"
#include "Points.hpp"
#include "IPrimitive.hpp"
namespace RayTracer {
    class RayCaster;
    class HitInfo;
    class ILights {
        private:

        public:
            ILights() = default;
            virtual ~ILights() = default;

            virtual Math::Vector3D getColor() const = 0;
            virtual double getIntensity() const = 0;
            virtual Math::Vector3D computeLightingColor(HitInfo &info, const RayCaster &raytracer) const = 0;
    };

}