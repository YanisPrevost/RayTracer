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
#include <vector>

namespace RayTracer
{
    class Plane : public IPrimitive
    {
        public:
            Plane(const std::vector<double>& params);
            Plane(const std::string& axis, const Math::Vector3D& position, const Math::Vector3D& color, double reflection = 0.0);
            ~Plane() override = default;

            HitInfo intersect(const Ray& ray) const override;
            std::string getName() const override;
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;

        private:
            Math::Vector3D position;
            Math::Vector3D normal;
            std::string axis;
            Math::Vector3D color;
            double reflection;

            void setNormal();
    };

}