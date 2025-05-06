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
            if (buffer[0] == 'g')
                break;
        }
        while (std::getline(file, buffer)) {
            if (buffer[0] == 'v')
                break;
        }
        char c = 'v';
        double x, y, z;
        std::stringstream bufferStream = std::stringstream(buffer);
        bufferStream >> c >> x >> y >> z;
        vertices.push_back(Math::Point3D(x, y, z));
        while (std::getline(file, buffer)) {
            bufferStream = std::stringstream(buffer);
            bufferStream >> c;
            if (c == 'v') {
                bufferStream >> x >> y >> z;
                vertices.push_back(Math::Point3D(x, y, z));
            } else {
                break;
            }
        }
        while (std::getline(file, buffer)) {
            if (buffer[0] == 'f')
                break;
        }
        int v1, v2, v3;
        bufferStream = std::stringstream(buffer);
        bufferStream >> c >> v1 >> v2 >> v3;
        _sides.push_back(std::vector<int>({v1, v2, v3}));
        while (std::getline(file, buffer)) {
            bufferStream = std::stringstream(buffer);
            bufferStream >> c;
            if (c == 'f') {
                bufferStream >> v1 >> v2 >> v3;
                _sides.push_back(std::vector<int>({v1, v2, v3}));
            } else {
                break;
            }
        }
        file.close();
        for (auto &i : vertices)
            std::cout << i.X << ' ' << i.Y << ' ' << i.Z << std::endl;
        for (auto &i : _sides)
        std::cout << i[0] << ' ' << i[1] << ' ' << i[2] << std::endl;
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