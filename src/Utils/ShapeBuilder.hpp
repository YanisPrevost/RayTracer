/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShapeBuilder.hpp
*/

#pragma once

#include "../Interfaces/IShape.hpp"
#include "../Points/Point3D.hpp"
#include "../Vectors/Vector3D.hpp"
#include "../Primitives/ShapeDecorator.hpp"
#include <memory>

namespace RayTracer {

    class ShapeBuilder {
        public:
            virtual ~ShapeBuilder() = default;
            virtual void reset() = 0;
            virtual void setPosition(const Math::Point3D& position) = 0;
            virtual std::unique_ptr<IShape> build() = 0;
    };

    class SphereBuilder : public ShapeBuilder {
        private:
            Math::Point3D center;
            double radius;
            int r, g, b;
        public:
            SphereBuilder() : center(Math::Point3D(0, 0, 0)), radius(1.0), r(255), g(0), b(0) {}
            void reset() override {
                center = Math::Point3D(0, 0, 0);
                radius = 1.0;
                r = 255;
                g = 0;
                b = 0;
            }
            void setPosition(const Math::Point3D& position) override {
                center = position;
            }
            SphereBuilder& setRadius(double radius) {
                this->radius = radius;
                return *this;
            }
            SphereBuilder& setColor(int r, int g, int b) {
                this->r = r;
                this->g = g;
                this->b = b;
                return *this;
            }
            std::unique_ptr<IShape> build() override;
    };

    class ShapeDirector {
        public:
            std::unique_ptr<IShape> createSphereAt(ShapeBuilder& builder, const Math::Point3D& position) {
                builder.setPosition(position);
                return builder.build();
            }
    };
}
