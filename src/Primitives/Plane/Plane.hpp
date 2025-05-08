/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Plane.hpp
*/

#pragma once

#include "../../Interfaces/IPrimitive.hpp"
#include <memory>
#include <string>

namespace RayTracer {

    enum class Axis {
        X, Y, Z
    };

    class Plane : public IPrimitive {
        private:
            Axis axis;
            double position;
            Math::Vector3D color;
            double reflection;

        public:
            Plane(Axis axis = Axis::Z,
                  double position = 0.0,
                  const Math::Vector3D& color = Math::Vector3D(1, 1, 1),
                  double reflection = 0.0);
            Plane(const std::vector<double>& params);
            Plane(ArgumentMap map);
            HitInfo intersect(const Ray& ray) const override;
            std::string getName() const override;
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;
            AABB getBoundingBox() {
                return AABB();
            }

            // Getters
            Axis getAxis() const { return axis; }
            double getPosition() const { return position; }
            Math::Vector3D getColor() const { return color; }
            double getReflection() const { return reflection; }

            // Setters
            void setAxis(Axis axis) { this->axis = axis; }
            void setPosition(double position) { this->position = position; }
            void setColor(const Math::Vector3D& color) { this->color = color; }
            void setReflection(double reflection) { this->reflection = reflection; }

            // Helper method to convert string to Axis enum
            static Axis stringToAxis(const std::string& axisStr);
    };

}
