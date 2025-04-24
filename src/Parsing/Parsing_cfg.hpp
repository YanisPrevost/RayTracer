/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.hpp
*/

#pragma once
#include <iostream>
#include <fstream>
#include "Points/Point3D.hpp"
#include <vector>

namespace RayTracer
{
    class Parsing_cfg {
        public:
            class Cam_info {
                public:
                    Cam_info() : _fov(90.0), _position(Math::Point3D(0, 30, 10)), _width(1270), _height(720) {}
                    double getFov() const { return _fov; }
                    Math::Point3D getPosition() const { return _position; }
                    int getWidth() const { return _width; }
                    int getHeight() const { return _height; }
                    void setFov(double fov) { _fov = fov; }
                    void setPosition(const Math::Point3D& position) { _position = position; }
                    void setWidth(int width) { _width = width; }
                    void setHeight(int height) { _height = height; }
                private:
                    double _fov;
                    Math::Point3D _position;
                    int _width;
                    int _height;
            };

            class Sphere_info {
                public:
                    Sphere_info() : _position(Math::Point3D(0, 8, 0)), _radius(10.0), _r(255), _g(0), _b(0) {}
                    Math::Point3D getPosition() const { return _position; }
                    double getRadius() const { return _radius; }
                    int getR() const { return _r; }
                    int getG() const { return _g; }
                    int getB() const { return _b; }
                    void setPosition(const Math::Point3D& position) { _position = position; }
                    void setRadius(double radius) { _radius = radius; }
                    void setColor(int r, int g, int b) { _r = r; _g = g; _b = b; }
                private:
                    Math::Point3D _position;
                    double _radius;
                    int _r;
                    int _g;
                    int _b;
            };

        private:
            const std::string _filename;
            Cam_info _camInfo;
            std::vector<Sphere_info> _sphereInfos;

        public:
            Parsing_cfg(const std::string& filename) : _filename(filename) {}
            ~Parsing_cfg() = default;
            void parse();

            const Cam_info& getCamInfo() const { return _camInfo; }
            const std::vector<Sphere_info>& getSphereInfos() const { return _sphereInfos; }
    };
}
