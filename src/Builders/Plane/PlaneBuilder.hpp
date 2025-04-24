/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneBuilder.hpp
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

    class PlaneBuilder : public IShapeBuilder {
        private:
            Math::Point3D position;
            std::string axis;
            int r, g, b;
        public:
            PlaneBuilder() : position(Math::Point3D(0, 0, 0)), axis("Z"), r(255), g(0), b(0) {}

            void reset() override {
                position = Math::Point3D(0, 0, 0);
                axis = "Z";
                r = 255;
                g = 0;
                b = 0;
            }
            void setPosition(const Math::Point3D& position) override {
                this->position = position;
            }
            PlaneBuilder& setAxis(const std::string& axis) {
                this->axis = axis;
                return *this;
            }
            PlaneBuilder& setColor(int r, int g, int b) {
                this->r = r;
                this->g = g;
                this->b = b;
                return *this;
            }
            std::unique_ptr<IShape> build() override;
        };

}