/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Sphere.hpp
*/

#pragma once

#include "IPrimitive.hpp"
#include <memory>
#include "../../Parsing/ArgumentMap.hpp"

namespace RayTracer {

    class Sphere : public IPrimitive {
        private:
            Math::Point3D center;
            double radius;
            Math::Vector3D color;
            double reflection = -1.0;

        public:
            Sphere(const Math::Point3D& center = Math::Point3D(0, 0, 0),
                double radius = 1.0,
                const Math::Vector3D& color = Math::Vector3D(1, 1, 1),
                double reflection = 0.0);
            Sphere(const std::vector<double>& params);
            Sphere(ArgumentMap params);
            HitInfo intersect(const Ray& ray) const override;
            std::string getName() const override;
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;
            AABB getBoundingBox() {
                return AABB();
            }

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
