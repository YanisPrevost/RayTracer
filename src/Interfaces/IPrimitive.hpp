/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** IPrimitive.hpp
*/

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <limits>
#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"
#include "../Interfaces/HitInfo.hpp"
#include "../Ray/Ray.hpp"
#include "../Parsing/ArgumentMap.hpp"
namespace RayTracer {

    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual HitInfo intersect(const Ray& ray) const = 0;
            virtual std::string getName() const = 0;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params) = 0;
    };

    extern "C" {
        const char *getPrimitiveName();
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap);
    }

}