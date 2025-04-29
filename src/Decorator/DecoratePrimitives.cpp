/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** DecoratePrimitives.cpp
*/

#include "DecoratePrimitives.hpp"

namespace RayTracer {

    APrimitiveDecorator::APrimitiveDecorator(std::unique_ptr<IPrimitive> primitive)
        : wrappedPrimitive(std::move(primitive))
    {
    }

    HitInfo APrimitiveDecorator::intersect(const Ray& ray) const
    {
        if (wrappedPrimitive) {
            return wrappedPrimitive->intersect(ray);
        }

        HitInfo info;
        info.hit = false;
        return info;
    }

    std::string APrimitiveDecorator::getName() const
    {
        if (wrappedPrimitive) {
            return "Decorated_" + wrappedPrimitive->getName();
        }
        return "EmptyDecorator";
    }

    // std::unique_ptr<IPrimitive> APrimitiveDecorator::create(const std::vector<double>& params)
    // {
    //     if (wrappedPrimitive) {
    //         return wrappedPrimitive->create(params);
    //     }
    //     return nullptr;
    // }

    ColorDecorator::ColorDecorator(std::unique_ptr<IPrimitive> primitive, const Math::Vector3D& color)
        : APrimitiveDecorator(std::move(primitive)), color(color)
    {
    }

    HitInfo ColorDecorator::intersect(const Ray& ray) const
    {
        HitInfo info = APrimitiveDecorator::intersect(ray);

        if (info.hit) {
            info.color = color;
        }
        return info;
    }

    std::string ColorDecorator::getName() const
    {
        return "Colored_" + APrimitiveDecorator::getName();
    }

    std::unique_ptr<IPrimitive> ColorDecorator::create(const std::vector<double>& params)
    {
        auto primitive = APrimitiveDecorator::create(params);
        if (!primitive) return nullptr;
        if (params.size() >= 3) {
            Math::Vector3D newColor(params[0], params[1], params[2]);
            return std::make_unique<ColorDecorator>(std::move(primitive), newColor);
        }
        return std::make_unique<ColorDecorator>(std::move(primitive), color);
    }

    ReflectionDecorator::ReflectionDecorator(std::unique_ptr<IPrimitive> primitive, double coefficient)
        : APrimitiveDecorator(std::move(primitive)), reflectionCoefficient(coefficient)
    {
    }

    HitInfo ReflectionDecorator::intersect(const Ray& ray) const
    {
        HitInfo info = APrimitiveDecorator::intersect(ray);
        if (info.hit) {
            info.reflection = reflectionCoefficient;
        }
        return info;
    }

    std::string ReflectionDecorator::getName() const
    {
        return "Reflective_" + APrimitiveDecorator::getName();
    }

    std::unique_ptr<IPrimitive> ReflectionDecorator::create(const std::vector<double>& params)
    {
        auto primitive = APrimitiveDecorator::create(params);
        if (!params.empty()) {
            double coef = params[0];
            return std::make_unique<ReflectionDecorator>(std::move(primitive), coef);
        }
        return std::make_unique<ReflectionDecorator>(std::move(primitive), reflectionCoefficient);
    }

    std::unique_ptr<IPrimitive> decoratePrimitive(std::unique_ptr<IPrimitive> primitive, const Math::Vector3D& color, double reflection)
    {
        if (primitive) {
            primitive = std::make_unique<ColorDecorator>(std::move(primitive), color);
            if (reflection > 0) {
                primitive = std::make_unique<ReflectionDecorator>(std::move(primitive), reflection);
            }
        }
        return primitive;
    }

}
