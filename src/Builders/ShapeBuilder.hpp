/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShapeBuilder.hpp
*/

#pragma once

#include "../Interfaces/IShape.hpp"
#include "../Interfaces/IShapeBuilder.hpp"
#include "../Points/Point3D.hpp"
#include "../Vectors/Vector3D.hpp"
#include "../Primitives/ShapeDecorator.hpp"
#include <memory>

namespace RayTracer {

    class ShapeDirector {
        public:
            // Buid method to create primitives
            std::unique_ptr<IShape> createSphere(IShapeBuilder& builder, const Math::Point3D& position) {
                builder.setPosition(position);
                return builder.build();
            }
    };
}
