/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Triangle
*/

#ifndef TRIANGLE_HPP_
#define TRIANGLE_HPP_
#include "IPrimitive.hpp"
#include "HitInfo.hpp"
#include <memory>
#include "Vector.hpp"
#include "Points.hpp"
#include "../Parsing/ArgumentMap.hpp"

namespace RayTracer {
    class Triangle : public IPrimitive {
        public:
            Triangle();
            Triangle(ArgumentMap params);
            ~Triangle();
            HitInfo intersect(const Ray& ray) const = 0;
            std::string getName() const = 0;
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params) = 0;
        protected:
        private:
            Math::Point3D vertex1;
            Math::Point3D vertex2;
            Math::Point3D vertex3;
    };
}

#endif /* !TRIANGLE_HPP_ */
