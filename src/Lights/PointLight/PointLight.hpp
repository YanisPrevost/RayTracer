/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** PointLight
*/

#ifndef POINTLIGHT_HPP_
#define POINTLIGHT_HPP_
#include "../../Vectors/Vector.hpp"
#include "../../Points/Points.hpp"
#include "../ALights.hpp"
#include "../../Interfaces/IPrimitive.hpp"
namespace RayTracer
{
    class PointLight : public ALights {
        public:
            PointLight(
                const Math::Point3D& pos,
                const Math::Vector3D& col,
                double intensity) : ALights(pos, col, intensity) {};
            ~PointLight();
            Math::Vector3D computeDiffuseLightingColor(HitInfo &info) const;
        protected:
        private:
    };
}

#endif /* !POINTLIGHT_HPP_ */
