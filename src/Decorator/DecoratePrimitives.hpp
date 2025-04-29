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

    class APrimitiveDecorator : public IPrimitive {
        protected:
            std::unique_ptr<IPrimitive> wrappedPrimitive;

        public:
            APrimitiveDecorator(std::unique_ptr<IPrimitive> primitive);
            virtual ~APrimitiveDecorator() = default;

            virtual HitInfo intersect(const Ray& ray) const override;
            virtual std::string getName() const override;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params) override;
    };

    class ColorDecorator : public APrimitiveDecorator {
        private:
            Math::Vector3D color;

        public:
            ColorDecorator(std::unique_ptr<IPrimitive> primitive, const Math::Vector3D& color);

            virtual HitInfo intersect(const Ray& ray) const override;
            virtual std::string getName() const override;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params);
    };

    class ReflectionDecorator : public APrimitiveDecorator {
        private:
            double reflectionCoefficient;

        public:
            ReflectionDecorator(std::unique_ptr<IPrimitive> primitive, double coefficient);

            virtual HitInfo intersect(const Ray& ray) const override;
            virtual std::string getName() const override;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params);
    };

    std::unique_ptr<IPrimitive> decoratePrimitive(std::unique_ptr<IPrimitive> primitive, const Math::Vector3D& color,double reflection);

}
