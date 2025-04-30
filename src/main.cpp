/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** main.cpp
*/

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <thread>
#include <chrono>
#include <dlfcn.h>
#include "Builder/RayTracer.hpp"
#include "Visualization/PpmViewer.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file.cfg>" << std::endl;
        return 1;
    }

    std::string configFile = argv[1];
    std::cout << "Analyse du fichier de configuration: " << configFile << std::endl;
    RayTracer::Parsing_cfg parser(configFile);
    parser.parse();

    const RayTracer::Cam_info& camInfo = parser.getCamInfo();
    RayTracer::RayTracer raytracer(camInfo.getWidth(), camInfo.getHeight());
    RayTracer::Camera camera(
        camInfo.getPosition(),
        Math::Vector3D(0, 0, -1),
        Math::Vector3D(0, 1, 0),
        camInfo.getFov()
    );
    raytracer.setCamera(camera);
    std::vector<std::string> primitiveTypes = {"Sphere", "Plane"};
    for (const auto& type : primitiveTypes) {
        std::string libPath = "./Plugins/Primitives/lib" + type + ".so";
        raytracer.loadPrimitiveLibrary(libPath, type);
    }

    raytracer.BuildScene(parser);

    std::cout << "Lancement du rendu...";

    RayTracer::PpmViewer viewer("", parser.getCamInfo());

    viewer.start_rendering(&raytracer);
    raytracer.start_rendering();

    int height = parser.getCamInfo().getHeight();
    while (raytracer.isRenderingActive() && raytracer.getCurrentLine() < height) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::string outputFile = "output.ppm";
    std::cout << "\nSauvegarde de l'image dans " << outputFile << std::endl;
    raytracer.saveImage(outputFile);

    std::cout << "Rendu terminé !" << std::endl;
    while (viewer.isDisplayActive()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}