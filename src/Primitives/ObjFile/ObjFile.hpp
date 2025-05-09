/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ObjFile
*/

#pragma once

#include "ArgumentMap.hpp"
#include "../DynamicLibrary/DynamicLibrary.hpp"
#include <vector>
#include "Points.hpp"
#include <memory>
#include "../../Interfaces/IPrimitive.hpp"
#include "../../BVHBuilder/AABB.hpp"
#include "../../BVHBuilder/BinaryTree.hpp"

namespace RayTracer {
    class ObjFile : public IPrimitive {
        public:
            ObjFile(ArgumentMap params);
            ~ObjFile();
            void parseObjFile(std::string fileName);
            std::vector<std::unique_ptr<IPrimitive>>  generateTriangles();
            HitInfo intersect(const Ray& ray) const;
            std::string getName() const
            {
                return "ObjFile";
            }
            std::unique_ptr<IPrimitive> create(const std::vector<double> &params)
            {
                return std::unique_ptr<IPrimitive>();
            }
            AABB getBoundingBox() {
                return AABB();
            }
        private:
            std::string fileName;
            DynamicLibrary triangleLib;
            std::vector<Math::Point3D>vertices;
            std::vector<std::vector<int>> _sides;
            std::unique_ptr<Node> tree;
            Math::Vector3D _color;
            Math::Point3D _position;
    };
}
