/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PositionedShape.hpp
*/

#pragma once

#include <memory>
#include "../Interfaces/IShape.hpp"
#include "../Points/Point3D.hpp"

namespace RayTracer {

    class PositionedShape : public IShape {
        private:
            std::unique_ptr<IShape> shape;
            Math::Point3D position;
            double scale;
        public:
            PositionedShape(std::unique_ptr<IShape> shape, const Math::Point3D& position, double scale = 1.0)
                : shape(std::move(shape)), position(position), scale(scale) {}
            bool hits(const Ray& ray) const override {
                Math::Vector3D translation = ray.getOrigin() - position;
                Math::Point3D newOrigin(
                    translation.getX(),
                    translation.getY(),
                    translation.getZ()
                );
                Math::Vector3D newDirection = ray.getDirection();
                Ray transformedRay(newOrigin, newDirection);
                return shape->hits(transformedRay);
            }
            const char* getType() const override {
                return shape->getType();
            }
    };
}
