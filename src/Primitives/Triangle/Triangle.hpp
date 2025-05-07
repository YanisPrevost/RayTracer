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
            HitInfo intersect(const Ray& ray) const;
            std::string getName() const { return "Triangle"; }
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params)
            {
                return std::make_unique<Triangle>();
            }
        protected:
        private:
            Math::Point3D vertex1;
            Math::Point3D vertex2;
            Math::Point3D vertex3;
            Math::Vector3D _color;
            Math::Vector3D edge1;
            Math::Vector3D edge2;
            Math::Vector3D normal;
    };
}

#endif /* !TRIANGLE_HPP_ */
