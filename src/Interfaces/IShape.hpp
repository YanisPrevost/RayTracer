/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** IShape.hpp
*/

#pragma once

#include "../Rays/Ray.hpp"
#include <memory>

namespace RayTracer {

    class IShape {
        public:
            virtual ~IShape() = default;
            virtual bool hits(const Ray& ray) const = 0;
            virtual const char* getType() const = 0;
        };

}

extern "C" {
    typedef RayTracer::IShape* (*create_shape_t)();
    typedef void (*destroy_shape_t)(RayTracer::IShape*);
}
