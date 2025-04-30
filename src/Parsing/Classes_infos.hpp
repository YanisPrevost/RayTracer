/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Classes.hpp
*/

#pragma once

#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"

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
            Plane_info() : _position(Math::Point3D(0, 0, 0)), _axis(""), _r(255), _g(0), _b(0) {}
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

    class Cones_Info {
        public:
            Cones_Info() : _position(Math::Point3D(0, 8, 0)), _radius(10.0), _height(10), _r(255), _g(0), _b(0) {}
            Math::Point3D getPosition() const { return _position; }
            int getHeight() const { return _height; }
            Math::Point3D getDirection() const { return _direction; }
            double getRadius() const { return _radius; }
            int getR() const { return _r; }
            int getG() const { return _g; }
            int getB() const { return _b; }
            void setPosition(const Math::Point3D& position) { _position = position; }
            void setDirection(const Math::Point3D& direction) { _direction = direction; }
            void setRadius(double radius) { _radius = radius; }
            void setHeight(int height) { _height = height; }
            void setColor(int r, int g, int b) { _r = r; _g = g; _b = b; }
        private:
            Math::Point3D _position;
            double _radius;
            int _height;
            Math::Point3D _direction;
            int _r;
            int _g;
            int _b;
    };

    class Light_Info {
        public:
            Light_Info() : _ambient(0.5), _diffuse(0.5) {}
            double getAmbient() const { return _ambient; }
            double getDiffuse() const { return _diffuse; }
            void setAmbient(double ambient) { _ambient = ambient; }
            void setDiffuse(double diffuse) { _diffuse = diffuse; }
        private:
            double _ambient;
            double _diffuse;
    };

    class Light_Point : public Light_Info {
        public:
            Light_Point() : _position(Math::Point3D(0, 0, 0)), _r(255), _g(255), _b(255) {}
            Light_Point(const Math::Point3D& position, int r, int g, int b)
                : _position(position), _r(r), _g(g), _b(b) {}
            Math::Point3D getPosition() const { return _position; }
            int getR() const { return _r; }
            int getG() const { return _g; }
            int getB() const { return _b; }
            void setPosition(const Math::Point3D& position) { _position = position; }
            void setColor(int r, int g, int b) { _r = r; _g = g; _b = b; }
            void setLightInfo(double ambient, double diffuse) {
                setAmbient(ambient);
                setDiffuse(diffuse);
            }
        private:
            Math::Point3D _position;
            int _r;
            int _g;
            int _b;
    };
    class Light_Direction : public Light_Info {
        public:
            Light_Direction() : _direction(Math::Point3D(0, 0, 0)), _intensity(1.0), _r(255), _g(255), _b(255) {}
            Math::Point3D getDirection() const { return _direction; }
            double getIntensity() const { return _intensity; }
            int getR() const { return _r; }
            int getG() const { return _g; }
            int getB() const { return _b; }
            void setDirection(const Math::Point3D& direction) { _direction = direction; }
            void setIntensity(double intensity) { _intensity = intensity; }
            void setColor(int r, int g, int b) { _r = r; _g = g; _b = b; }
            void setLightInfo(double ambient, double diffuse) {
                setAmbient(ambient);
                setDiffuse(diffuse);
            }

        private:
            Math::Point3D _direction;
            double _intensity;
            int _r;
            int _g;
            int _b;
    };
}