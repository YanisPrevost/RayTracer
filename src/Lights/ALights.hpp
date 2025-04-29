/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ALights
*/

#ifndef ALIGHTS_HPP_
#define ALIGHTS_HPP_
#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"
#include "../Interfaces/ILights.hpp"
#include "../Interfaces/IPrimitive.hpp"
namespace RayTracer {
    class ALights : public ILights {
        public:
            ALights(
                const Math::Point3D& pos,
                const Math::Vector3D& col,
                double intensity)
                : _position(pos), _color(col), _intensity(intensity) {};
            ~ALights();
            Math::Point3D getPosition() const;
            Math::Vector3D getColor() const;
            double getIntensity() const;
            virtual Math::Vector3D computeDiffuseLightingColor(HitInfo &info) const = 0;
        protected:
            Math::Point3D _position;
            Math::Vector3D _color;
            double _intensity;
        private:
    };
}
#endif /* !ALIGHTS_HPP_ */
