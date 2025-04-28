/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** DecoratePrimitives.hpp
*/

#pragma once
#include "../Interfaces/IPrimitive.hpp"
#include <memory>

namespace RayTracer {

    class PrimitiveDecorator : public IPrimitive {
        protected:
            std::unique_ptr<IPrimitive> wrappedPrimitive;

        public:
            PrimitiveDecorator(std::unique_ptr<IPrimitive> primitive);
            virtual ~PrimitiveDecorator() = default;

            virtual HitInfo intersect(const Ray& ray) const override;
            virtual std::string getName() const override;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;
    };

    class ColorDecorator : public PrimitiveDecorator {
        private:
        Math::Vector3D color;

        public:
            ColorDecorator(std::unique_ptr<IPrimitive> primitive, const Math::Vector3D& color);

            virtual HitInfo intersect(const Ray& ray) const override;
            virtual std::string getName() const override;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;
    };

    class ReflectionDecorator : public PrimitiveDecorator {
        private:
            double reflectionCoefficient;

        public:
            ReflectionDecorator(std::unique_ptr<IPrimitive> primitive, double coefficient);

            virtual HitInfo intersect(const Ray& ray) const override;
            virtual std::string getName() const override;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;
    };

    std::unique_ptr<IPrimitive> decoratePrimitive(std::unique_ptr<IPrimitive> primitive, const Math::Vector3D& color,double reflection);

}
