/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ObjFile
*/

#ifndef OBJFILE_HPP_
#define OBJFILE_HPP_
#include "ArgumentMap.hpp"
#include "../DynamicLibrary/DynamicLibrary.hpp"
#include <vector>
#include "Points.hpp"
#include <memory>
#include "../../Interfaces/IPrimitive.hpp"

namespace RayTracer {
    class ObjFile : public IPrimitive {
        public:
            ObjFile(ArgumentMap params);
            ~ObjFile();
            void parseObjFile(std::string fileName);
            void generateTriangles();
            HitInfo intersect(const Ray& ray) const;
            std::string getName() const
            {
                return "ObjFile";
            }
            std::unique_ptr<IPrimitive> create(const std::vector<double> &params)
            {
                return std::unique_ptr<IPrimitive>();
            }
        protected:
        private:
            std::string fileName;
            DynamicLibrary triangleLib;
            std::vector<Math::Point3D>vertices;
            std::vector<std::vector<int>> _sides;
            std::vector<std::unique_ptr<IPrimitive>> triangles;
    };
}
#endif /* !OBJFILE_HPP_ */
