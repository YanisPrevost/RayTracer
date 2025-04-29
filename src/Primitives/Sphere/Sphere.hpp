/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Sphere.hpp
*/

#pragma once

#include "../../Interfaces/IPrimitive.hpp"
#include <memory>

namespace RayTracer {

    class Sphere : public IPrimitive {
        private:
            Math::Point3D center;
            double radius;
            Math::Vector3D color;
            double reflection;

        public:
            Sphere(const Math::Point3D& center = Math::Point3D(0, 0, 0),
                double radius = 1.0,
                const Math::Vector3D& color = Math::Vector3D(1, 1, 1),
                double reflection = 0.0);
            Sphere(const std::vector<double>& params);
            HitInfo intersect(const Ray& ray) const override;
            std::string getName() const override;
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;

            Math::Point3D getCenter() const { return center; }
            double getRadius() const { return radius; }
            Math::Vector3D getColor() const { return color; }
            double getReflection() const { return reflection; }

            void setCenter(const Math::Point3D& center) { this->center = center; }
            void setRadius(double radius) { this->radius = radius; }
            void setColor(const Math::Vector3D& color) { this->color = color; }
            void setReflection(double reflection) { this->reflection = reflection; }
        };

}
