/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-raytracer-yanis.prevost
** File description:
** create.cpp
*/

#include "Camera/Camera.hpp"
#include "Utils/ShapeBuilder.hpp"
#include "Utils/utils.hpp"
#include "Visualization/PpmViewer.hpp"
#include "Primitives/ShapeDecorator.hpp"
#include "Parsing/Parsing_cfg.hpp"
#include <cstring>
#include <iostream>

namespace RayTracer {

void Parsing_cfg::create(std::vector<std::unique_ptr<RayTracer::IShape>> shapes, RayTracer::SphereBuilder sphereBuilder, 
                         RayTracer::ShapeDirector director, RayTracer::Camera cam) {
    const int width = 1270;
    const int height = 720;
    double fov = 90.0;

    RayTracer::Camera cam(Math::Point3D(0, 30, 10), fov, width, height);

    std::cout << "Construction des formes avec le pattern Builder..." << std::endl;

    sphereBuilder.setColor(0, 0, 255).setRadius(10.0); // Couleur bleue
    shapes.push_back(director.createSphereAt(sphereBuilder, Math::Point3D(0, 5, 0)));

    sphereBuilder.setColor(0, 255, 0).setRadius(15.0); // Couleur verte
    shapes.push_back(director.createSphereAt(sphereBuilder, Math::Point3D(0, 8, 0)));
    }
}