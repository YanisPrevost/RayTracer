/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ALights
*/

#pragma once

#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"
#include "../Interfaces/ILights.hpp"
#include "../Interfaces/IPrimitive.hpp"

namespace RayTracer {

    class ALights : public ILights {
        public:
            ALights(const Math::Vector3D& col,
                double intensity)
                : _color(col), _intensity(intensity) {}
            ~ALights();
            Math::Vector3D getColor() const;
            double getIntensity() const;
            virtual Math::Vector3D computePointLightingColor(HitInfo &info, const RayTracer &raytracer) const = 0;
        private:
            Math::Vector3D _color;
            double _intensity;
    };

}
