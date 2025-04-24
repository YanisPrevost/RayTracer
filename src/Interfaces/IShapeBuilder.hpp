/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** IShapeBuilder.hpp
*/

#pragma once

#include "IShape.hpp"
#include "../Points/Point3D.hpp"
#include <memory>

namespace RayTracer {

    class IShapeBuilder {
        public:
            virtual ~IShapeBuilder() = default;
            virtual void reset() = 0;
            virtual void setPosition(const Math::Point3D& position) = 0;
            virtual std::unique_ptr<IShape> build() = 0;
        };

}
