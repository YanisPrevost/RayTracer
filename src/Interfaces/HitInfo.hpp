/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** HitInfo
*/

#ifndef HITINFO_HPP_
#define HITINFO_HPP_
#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"

namespace RayTracer {
    class HitInfo {
        public:
            bool hit;
            double distance;
            Math::Point3D point;
            Math::Vector3D normal;
            Math::Vector3D color;
            double reflection;
    };
}
#endif /* !HITINFO_HPP_ */
