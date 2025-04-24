/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShpereBuidler.hpp
*/

#pragma once

#include "Interfaces/IShape.hpp"
#include "Interfaces/IShapeBuilder.hpp"
#include "Decorator/ShapeDecorator.hpp"
#include "Decorator/PositionedShape.hpp"
#include <memory>
#include <dlfcn.h>
#include <iostream>

namespace RayTracer {

    class SphereBuilder : public IShapeBuilder {
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

}