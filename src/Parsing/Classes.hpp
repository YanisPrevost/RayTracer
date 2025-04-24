/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Classes.hpp
*/

#pragma once

#include "Parsing_cfg.hpp"

namespace RayTracer
{
    class Cam_info {
        public:
            Cam_info() : _fov(90.0), _position(Math::Point3D(0, 0, 0)), _width(800), _height(600) {}
            double getFov() const { return _fov; }
            Math::Point3D getPosition() const { return _position; }
            int getWidth() const { return _width; }
            int getHeight() const { return _height; }
            void setFov(double fov) { _fov = fov; }
            void setPosition(const Math::Point3D& position) { _position = position; }
            void setWidth(int width) { _width = width; }
            void setHeight(int height) { _height = height; }
            double _fov;
            Math::Point3D _position;
            Math::Point3D _rotation;
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

    class Plane_info {
        public:
            Plane_info() : _position(Math::Point3D(0, 0, 0)), _axis("Z"), _r(255), _g(0), _b(0) {}
            Math::Point3D getPosition() const { return _position; }
            std::string getAxis() const { return _axis; }
            int getR() const { return _r; }
            int getG() const { return _g; }
            int getB() const { return _b; }
            void setPosition(const Math::Point3D& position) { _position = position; }
            void setAxis(const std::string& axis) { _axis = axis; }
            void setColor(int r, int g, int b) { _r = r; _g = g; _b = b; }
        private:
            Math::Point3D _position;
            std::string _axis;
            int _r;
            int _g;
            int _b;
    };
}