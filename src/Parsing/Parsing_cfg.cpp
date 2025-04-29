/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.cpp
*/

#include "Parsing_cfg.hpp"

namespace RayTracer
{

    void Parsing_cfg::parseCamera(libconfig::Config& cfg)
    {
        int x, y, z;
        if (cfg.exists("camera")) {
            cfg.lookupValue("camera.fieldOfView", _camInfo._fov);
            cfg.lookupValue("camera.resolution.width", _camInfo._width);
            cfg.lookupValue("camera.resolution.height", _camInfo._height);

            if (cfg.lookupValue("camera.position.x", x) && cfg.lookupValue("camera.position.y", y) && cfg.lookupValue("camera.position.z", z))
                _camInfo._position = Math::Point3D(x, y, z);

            if (cfg.lookupValue("camera.rotation.x", x) && cfg.lookupValue("camera.rotation.y", y) && cfg.lookupValue("camera.rotation.z", z))
                _camInfo._rotation = Math::Point3D(x, y, z);
            else
                _camInfo._rotation = Math::Point3D(0, 0, 0);
        }
    }

    void Parsing_cfg::parsePlanes(libconfig::Config& cfg)
    {
        libconfig::Setting& planes = cfg.lookup("primitives.planes");
        int numPlanes = planes.getLength();
        for (int i = 0; i < numPlanes; ++i) {
            libconfig::Setting& plane = planes[i];
            Plane_info planeInfo;
            std::string axis;
            int position;
            int r, g, b;

            plane.lookupValue("axis", axis);
            plane.lookupValue("position", position);

            const libconfig::Setting& color = plane["color"];
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);

            if (axis == "X") {
                planeInfo.setPosition(Math::Point3D(position, 0, 0));
            } else if (axis == "Y") {
                planeInfo.setPosition(Math::Point3D(0, position, 0));
            } else if (axis == "Z") {
                planeInfo.setPosition(Math::Point3D(0, 0, position));
            } else {
                // EXCEPTION A FAIRE ICI
            }
            planeInfo.setColor(r, g, b);
            _planeInfos.push_back(planeInfo);
        }
    }

    void Parsing_cfg::parseCones(libconfig::Config& cfg)
    {
        libconfig::Setting& cones = cfg.lookup("primitives.cones");
        int numCones = cones.getLength();
        for (int i = 0; i < numCones; ++i) {
            libconfig::Setting& cones = cones[i];
            Cones_Info conesInfo;
            std::string axis;
            int position;
            double radius;
            int _height;
            int r, g, b;

            cones.lookupValue("axis", axis);
            cones.lookupValue("position", position);
            cones.lookupValue("hength", _height);
            cones.lookupValue("r", radius);

            const libconfig::Setting& color = cones["color"];
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);

            if (axis == "X") {
                conesInfo.setPosition(Math::Point3D(position, 0, 0));
            } else if (axis == "Y") {
                conesInfo.setPosition(Math::Point3D(0, position, 0));
            } else if (axis == "Z") {
                conesInfo.setPosition(Math::Point3D(0, 0, position));
            } else {
                // EXCEPTION A FAIRE ICI
            }
            conesInfo.setAxis(axis);
            conesInfo.setHeight(_height);
            conesInfo.setRadius(radius);
            conesInfo.setColor(r, g, b);
            _conesInfos.push_back(conesInfo);
        }
    }

    void Parsing_cfg::parseSpheres(libconfig::Config& cfg)
    {
        libconfig::Setting& spheres = cfg.lookup("primitives.spheres");
        int numSpheres = spheres.getLength();
        for (int i = 0; i < numSpheres; ++i) {
            libconfig::Setting& sphere = spheres[i];
            Sphere_info sphereInfo;
            int x, y, z;
            int radius = 0;
            int r, g, b;
            sphere.lookupValue("x", x);
            sphere.lookupValue("y", y);
            sphere.lookupValue("z", z);
            sphere.lookupValue("r", radius);
            const libconfig::Setting& color = sphere["color"];
            color.lookupValue("r", r);
            color.lookupValue("g", g);
            color.lookupValue("b", b);
            sphereInfo.setPosition(Math::Point3D(x, y, z));
            sphereInfo.setRadius(radius);
            sphereInfo.setColor(r, g, b);
            _sphereInfos.push_back(sphereInfo);
        }
    }

    void Parsing_cfg::parse() {

        libconfig::Config cfg;
        std::fstream file(_filename.c_str());
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << _filename << std::endl;
            exit(84);
        }
        file.close();
        cfg.readFile(_filename.c_str());

        parseCamera(cfg);

        if (cfg.exists("primitives")) {
            parseSpheres(cfg);
            parsePlanes(cfg);
            // parseCones(cfg);
        }
    }
}