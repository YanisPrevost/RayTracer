/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** HitInfo
*/

#pragma once

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

            HitInfo() : hit(false), distance(0.0), point(), normal(), color(), reflection(0.0) {}
    };
}