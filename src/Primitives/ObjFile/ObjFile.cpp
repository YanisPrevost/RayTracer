/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ObjFile
*/

#include "ObjFile.hpp"
#include "ArgumentMap.hpp"
#include <fstream>
#include <vector>
#include <sstream>
#include <iostream>

namespace RayTracer {
    ObjFile::ObjFile(ArgumentMap params) : triangleLib("./Plugins/Primitives/libTriangle.so")
    {
        fileName = params["filename"].as<std::string>();
        parseObjFile(fileName);
        generateTriangles();
    }

    ObjFile::~ObjFile()
    {
    }

    void ObjFile::generateTriangles()
    {
        auto constructor = triangleLib.getConstructor<IPrimitive, ArgumentMap>("createPrimitive");
        for (auto &indices : this->_sides) {
            auto vertex1 = vertices[indices[0] - 1];
            auto vertex2 = vertices[indices[1] - 1];
            auto vertex3 = vertices[indices[2] - 1];
            ArgumentMap params;
            ArgumentMap vertexParam;
            vertexParam["x"] = vertex1.X;
            vertexParam["y"] = vertex1.Y;
            vertexParam["z"] = vertex1.Z;
            params["vertex1"] = vertexParam;
            ArgumentMap vertexParam2;
            vertexParam2["x"] = vertex2.X;
            vertexParam2["y"] = vertex2.Y;
            vertexParam2["z"] = vertex2.Z;
            params["vertex2"] = vertexParam2;
            ArgumentMap vertexParam3;
            vertexParam3["x"] = vertex3.X;
            vertexParam3["y"] = vertex3.Y;
            vertexParam3["z"] = vertex3.Z;
            params["vertex3"] = vertexParam3;
            params["color"] = Math::Vector3D(0, 0, 1);
            triangles.push_back(constructor(params));
        }
    }

    void ObjFile::parseObjFile(std::string fileName)
    {
        std::fstream file(fileName);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
        std::string buffer;
        while (std::getline(file, buffer)) {
            if (buffer[0] == 'v') {
                double x, y, z;
                std::stringstream bufferStream(buffer.substr(1));
                bufferStream >> x >> y >> z;
                vertices.push_back(Math::Point3D(x, y, z));
            }
            if (buffer[0] == 'f') {
                int v1, v2, v3;
                std::stringstream bufferStream = std::stringstream(buffer.substr(1));
                bufferStream  >> v1 >> v2 >> v3;
                _sides.push_back(std::vector<int>({v1, v2, v3}));
            }
        }
        file.close();
    }

    HitInfo ObjFile::intersect(const Ray& ray) const
    {
        HitInfo closestHit;
        closestHit.hit = false;
        for (auto &triangle : triangles) {
            auto hit = triangle->intersect(ray);
            if (hit.hit && (!closestHit.hit || hit.distance < closestHit.distance)) {
                closestHit = hit;
            }
        }
        return closestHit;
    }
}

// int main()
// {
//     RayTracer::ArgumentMap params;
//     params["filename"] = "model/solids.obj";
//     RayTracer::ObjFile obj(params);
//     obj.parseObjFile("model/solids.obj");
//     obj.generateTriangles();
// }

extern "C" {
    const char *getPrimitiveName() {
        return "objfiles";
    }
    std::unique_ptr<RayTracer::IPrimitive> createPrimitive(RayTracer::ArgumentMap params) {
        return std::make_unique<RayTracer::ObjFile>(params);
    }
}