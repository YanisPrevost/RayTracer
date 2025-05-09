/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** BinaryTree
*/

#include "BinaryTree.hpp"

namespace RayTracer {
    Node::Node(std::vector<std::unique_ptr<IPrimitive>> items)
    {
        if (items.empty())
            return;
            boundingBox = AABB({0, 0, 0}, {0, 0, 0});
        for (auto &item : items) {
            boundingBox = boundingBox + item->getBoundingBox();
        }
        if (items.size() <= 2) {
            objects = std::move(items);
            return;
        }
        Math::Point3D min;
        Math::Point3D max;
        min = items[0]->getBoundingBox().getCentroid();
        max = items[0]->getBoundingBox().getCentroid();
        for (auto &item : items) {
            Math::Point3D centroid = item->getBoundingBox().getCentroid();
            if (centroid.X < min.X)
                min.X = centroid.X;
            if (centroid.Y < min.Y)
                min.Y = centroid.Y;
            if (centroid.Z < min.Z)
                min.Z = centroid.Z;
            if (centroid.X > max.X)
                max.X = centroid.X;
            if (centroid.Y > max.Y)
                max.Y = centroid.Y;
            if (centroid.Z > max.Z)
                max.Z = centroid.Z;
        }
        Math::Vector3D extent = max - min;
        int axis = 0;
        if (extent.Y > extent.X)
            axis = 1;
        if (axis == 1)
            if (extent.Z > extent.Y)
                axis = 2;
        if (axis == 0)
            if (extent.Z > extent.X)
                axis = 2;
        std::sort(items.begin(), items.end(), [axis](const std::unique_ptr<IPrimitive> &a, const std::unique_ptr<IPrimitive> &b) {
            Math::Point3D centerA = a->getBoundingBox().getCentroid();
            Math::Point3D centerB = b->getBoundingBox().getCentroid();
            switch (axis) {
            case 0:
                return centerA.X < centerB.X;
            case 1:
                return centerA.Y < centerB.Y;
            case 2:
            default:
                return centerA.Z < centerB.Z;
            }
        });
        size_t middle = items.size() / 2;
        std::vector<std::unique_ptr<IPrimitive>> leftList;
        std::vector<std::unique_ptr<IPrimitive>> rightList;
        auto middleIter = items.begin() + middle;

        leftList.reserve(middle);
        rightList.reserve(items.size() - middle);

        std::move(std::make_move_iterator(items.begin()),
            std::make_move_iterator(items.begin() + middle),
            std::back_inserter(leftList));

        std::move(std::make_move_iterator(items.begin() + middle),
                std::make_move_iterator(items.end()),
                std::back_inserter(rightList));

        left = std::make_unique<Node>(std::move(leftList));
        right = std::make_unique<Node>(std::move(rightList));
    }
}