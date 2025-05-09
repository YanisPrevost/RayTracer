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
    ObjFile::ObjFile(ArgumentMap params) : triangleLib("./Plugins/Primitives/libTriangle.so"), fileName(params["filename"].as<std::string>())
    {
        parseObjFile(fileName);
        _color = params["color"].as<Math::Vector3D>();
        _position = params["position"].as<Math::Point3D>();
        auto res =  generateTriangles();
        tree = std::make_unique<Node>(std::move(res));
    }

    ObjFile::~ObjFile()
    {
    }

    std::vector<std::unique_ptr<IPrimitive>> ObjFile::generateTriangles()
    {
        std::vector<std::unique_ptr<IPrimitive>> triangles;
        auto constructor = triangleLib.getConstructor<IPrimitive, ArgumentMap>("createPrimitive");
        for (auto &indices : this->_sides) {
            auto vertex1 = vertices[indices[0] - 1];
            auto vertex2 = vertices[indices[1] - 1];
            auto vertex3 = vertices[indices[2] - 1];
            ArgumentMap params;
            ArgumentMap vertexParam;
            vertexParam["x"] = vertex1.X + _position.X;
            vertexParam["y"] = vertex1.Y + _position.Y;
            vertexParam["z"] = vertex1.Z + _position.Z;
            params["vertex1"] = vertexParam;
            ArgumentMap vertexParam2;
            vertexParam2["x"] = vertex2.X + _position.X;
            vertexParam2["y"] = vertex2.Y + _position.Y;
            vertexParam2["z"] = vertex2.Z + _position.Z;
            params["vertex2"] = vertexParam2;
            ArgumentMap vertexParam3;
            vertexParam3["x"] = vertex3.X + _position.X;
            vertexParam3["y"] = vertex3.Y + _position.Y;
            vertexParam3["z"] = vertex3.Z + _position.Z;
            params["vertex3"] = vertexParam3;
            params["color"] = _color;
            triangles.push_back(constructor(params));
        }
        return triangles;
    }

    void ObjFile::parseObjFile(std::string fileName)
    {
        std::fstream file(fileName);
        if (!file.is_open()) {
            throw std::runtime_error("Unable to open file");
        }
        std::string buffer;
        while (std::getline(file, buffer)) {
            if (buffer.rfind("v ", 0) == 0) {
                double x, y, z;
                std::stringstream bufferStream(buffer.substr(2));
                bufferStream >> x >> y >> z;
                vertices.push_back(Math::Point3D(x, y, z));
            }
            if (buffer.rfind("f ", 0) == 0) {
                std::string v1Str, v2Str, v3Str;
                int v1, v2, v3;
                std::stringstream bufferStream(buffer.substr(2));
                bufferStream >> v1Str >> v2Str >> v3Str;
                std::replace(v1Str.begin(), v1Str.end(), '/', ' ');
                std::stringstream xBufferStream(v1Str);
                xBufferStream >> v1;
                std::replace(v2Str.begin(), v2Str.end(), '/', ' ');
                std::stringstream yBufferStream(v2Str);
                yBufferStream >> v2;
                std::replace(v3Str.begin(), v3Str.end(), '/', ' ');
                std::stringstream zBufferStream(v3Str);
                zBufferStream >> v3;
                _sides.push_back(std::vector<int>({v1, v2, v3}));
            }
        }
        std::cout << "rendering " << _sides.size() << " polygons\n";
        file.close();
    }

    HitInfo ObjFile::intersect(const Ray& ray) const
    {
        HitInfo closestHit;
        closestHit.hit = false;
        closestHit = tree->intersects(ray);
        return closestHit;
    }

    extern "C" {
        const char *getPrimitiveName() {
            return "objfiles";
        }
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap params) {
            return std::make_unique<ObjFile>(params);
        }
    }
}