/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** BoundingBox
*/

#ifndef BOUNDINGBOX_HPP_
#define BOUNDINGBOX_HPP_
#include "IPrimitive.hpp"
#include "../BVHBuilder/AABB.hpp"

namespace RayTracer {
    class BoundingBox : public IPrimitive {
        public:
            BoundingBox();
            BoundingBox(ArgumentMap params);
            ~BoundingBox();

            HitInfo intersect(const Ray& ray) const;
            std::string getName() const { return "BoundingBox";}
            std::unique_ptr<IPrimitive> create(const std::vector<double>& params) { return std::make_unique<BoundingBox>();};
            AABB getBoundingBox() {
                return axisAlignedBoundingBox;
            }

        protected:
        private:
            AABB axisAlignedBoundingBox;
    };
}
#endif /* !BOUNDINGBOX_HPP_ */
