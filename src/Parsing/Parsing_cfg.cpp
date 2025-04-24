/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.cpp
*/

#include "Parsing_cfg.hpp"
#include <libconfig.h++>

namespace RayTracer
{
    void Parsing_cfg::parse() {

        libconfig::Config cfg;

        cfg.readFile(_filename.c_str());

        // Parsing camera informations

        // Parsing Primitives informations

        Sphere_info sphereInfo;
        sphereInfo.setPosition(Math::Point3D(0, 8, 0));
        sphereInfo.setRadius(10.0);
        sphereInfo.setColor(255, 0, 0);
        _sphereInfos.push_back(sphereInfo);

    }
}