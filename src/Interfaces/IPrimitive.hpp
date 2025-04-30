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

    class Ray {
        public:
            Math::Point3D origin;
            Math::Vector3D direction;

            Ray() = default;
            Ray(const Math::Point3D& o, const Math::Vector3D& d) : origin(o), direction(d) {}
            HitInfo find_intersection(const std::vector<std::unique_ptr<class IPrimitive>> &primitives) const;
    };

    class IPrimitive {
        public:
            virtual ~IPrimitive() = default;
            virtual HitInfo intersect(const Ray& ray) const = 0;
            virtual std::string getName() const = 0;
            virtual std::unique_ptr<IPrimitive> create(const std::vector<double>& params) = 0;
    };

    inline HitInfo Ray::find_intersection(const std::vector<std::unique_ptr<IPrimitive>> &primitives) const
    {
        HitInfo closestHit;
        closestHit.hit = false;
        closestHit.distance = std::numeric_limits<double>::max();
        for (const auto& element : primitives) {
            HitInfo hitInfo = element->intersect(*this);
            if (hitInfo.hit && hitInfo.distance < closestHit.distance && hitInfo.distance > 1e-6) {
                closestHit = hitInfo;
            }
        }
        return closestHit;
    }

    extern "C" {
        std::unique_ptr<IPrimitive> createPrimitive(const std::vector<double>& params);
    }

}