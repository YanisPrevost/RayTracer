/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.cpp
*/

#include "Parsing_cfg.hpp"

namespace RayTracer
{
    void Parsing_cfg::parse() {

        libconfig::Config cfg;

        cfg.readFile(_filename.c_str());

        // Parsing camera informations

        int x, y, z;
        cfg.lookupValue("camera.fieldOfView", _camInfo._fov);
        cfg.lookupValue("camera.resolution.width", _camInfo._width);
        cfg.lookupValue("camera.resolution.height", _camInfo._height);

        if (cfg.lookupValue("camera.position.x", x) && cfg.lookupValue("camera.position.y", y) && cfg.lookupValue("camera.position.z", z))
            _camInfo._position = Math::Point3D(x, y, z);

        if (cfg.lookupValue("camera.rotation.x", x) && cfg.lookupValue("camera.rotation.y", y) && cfg.lookupValue("camera.rotation.z", z))
            _camInfo._rotation = Math::Point3D(x, y, z);
        else
            _camInfo._rotation = Math::Point3D(0, 0, 0);


        // Parsing Primitives informations

        if (cfg.exists("primitives")) {
            libconfig::Setting& spheres = cfg.lookup("primitives.spheres");
            int numSpheres = spheres.getLength();
            for (int i = 0; i < numSpheres; ++i) {
                libconfig::Setting& sphere = spheres[i];
                Sphere_info sphereInfo;
                int x, y, z;
                double radius;
                int r, g, b;

                sphere.lookupValue("position.x", x);
                sphere.lookupValue("position.y", y);
                sphere.lookupValue("position.z", z);
                sphere.lookupValue("radius", radius);
                sphere.lookupValue("color.r", r);
                sphere.lookupValue("color.g", g);
                sphere.lookupValue("color.b", b);

                sphereInfo.setPosition(Math::Point3D(x, y, z));
                sphereInfo.setRadius(radius);
                sphereInfo.setColor(r, g, b);
                _sphereInfos.push_back(sphereInfo);
            }
        }
    }
}