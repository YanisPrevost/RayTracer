/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** AABB
*/

#ifndef AABB_HPP_
#define AABB_HPP_
#include "../Ray/Ray.hpp"
// #include "IPrimitive.hpp"

namespace RayTracer {
    class AABB {
        public:
            AABB();
            AABB(Math::Point3D min, Math::Point3D max) : _min(min), _max(max) {
                centroid = (min + max) * 0.5;
            }
            ~AABB();
            HitInfo getHitInfo(const Ray& ray) const;

            AABB operator+(AABB other)
            {
                Math::Point3D min = Math::Point3D (
                    std::min(other._min.X, this->_min.X),
                    std::min(other._min.Y, this->_min.Y),
                    std::min(other._min.Z, this->_min.Z)
                );
                Math::Point3D max = Math::Point3D (
                    std::max(other._max.X, this->_max.X),
                    std::max(other._max.Y, this->_max.Y),
                    std::max(other._max.Z, this->_max.Z)
                );
                return AABB(min, max);
            }
            const Math::Point3D &getCentroid() const
            {
                return centroid;
            }
            const Math::Point3D &getMin() const {return _min;}
            const Math::Point3D &getMax() const {return _max;}
        protected:
        private:
            Math::Point3D _min;
            Math::Point3D _max;
            std::pair<double, double> calculateEntryPoint(const Ray& ray) const;
            Math::Point3D centroid;
    };
}
#endif /* !AABB_HPP_ */
