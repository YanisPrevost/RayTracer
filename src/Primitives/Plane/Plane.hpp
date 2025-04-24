/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Plane.hpp
*/

#include <cmath>
#include <iostream>
#include <string>
#include "../../Vectors/Vector3D.hpp"
#include "../../Points/Point3D.hpp"
#include "../../Rays/Ray.hpp"
#include "../../Interfaces/IShape.hpp"

namespace RayTracer {

    class Plane : public IShape {
        private:
            Math::Point3D position;
            std::string axis;
        public:
            Plane();
            Plane(const Math::Point3D& point, const std::string& axis);

            bool hits(const Ray& ray) const override;
            const char* getType() const override { return "Plane"; }
        };
}
