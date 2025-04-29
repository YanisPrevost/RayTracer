/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ILights.hpp
*/

#pragma once
#include <memory>
#include "../Math/Vector3D.hpp"
#include "../Math/Point3D.hpp"

namespace RayTracer {

    class ILights {
        private:
            Math::Point3D position;
            Math::Vector3D color;
            double intensity;
        public:
            ILights(const Math::Point3D& pos, const Math::Vector3D& col, double intensity) : position(pos), color(col), intensity(intensity) {}
            virtual ~ILights() = default;

            Math::Point3D getPosition() const;
            Math::Vector3D getColor() const;
            double getIntensity() const;
    };

}