/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShapeDecorator.hpp
*/

#pragma once

#include <memory>
#include "../Interfaces/IShape.hpp"

namespace RayTracer {
    class ShapeDecorator : public IShape {
        protected:
            std::unique_ptr<IShape> decoratedShape;
        public:
            ShapeDecorator(std::unique_ptr<IShape> shape) : decoratedShape(std::move(shape)) {}
            virtual ~ShapeDecorator() = default;
            bool hits(const Ray& ray) const override {
                return decoratedShape->hits(ray);
            }
            const char* getType() const override {
                return decoratedShape->getType();
            }
    };

    class ColoredShape : public ShapeDecorator {
        private:
            int r, g, b;
        public:
            ColoredShape(std::unique_ptr<IShape> shape, int r, int g, int b) : ShapeDecorator(std::move(shape)), r(r), g(g), b(b) {}
            int getRed() const { return r; }
            int getGreen() const { return g; }
            int getBlue() const { return b; }
            const char* getType() const override {
                return "ColoredShape";
            }
    };
}
