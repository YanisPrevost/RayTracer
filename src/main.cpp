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

    // const RayTracer::Cam_info& camInfo = parser.getCamInfo();
    RayTracer::ArgumentMap &cameraInfo = parser.getCamInfo();
    auto &resolution = cameraInfo["resolution"].as<RayTracer::ArgumentMap>();
    int width = resolution["width"].as<int>();
    int height = resolution["height"].as<int>();
    RayTracer::RayTracer raytracer(width, height);
    raytracer.loadPrimitiveLibrary();
    raytracer.loadLightLibrary();
    auto &position = cameraInfo["position"].as<RayTracer::ArgumentMap>();
    Math::Point3D pos = Math::Point3D(position["x"].as<int>(), position["y"].as<int>(), position["z"].as<int>());
    RayTracer::Camera camera(
        pos,
        Math::Vector3D(0, 0, -1),
        Math::Vector3D(0, 1, 0),
        cameraInfo["fieldOfView"].as<double>()
    );
    raytracer.setCamera(camera);

    raytracer.BuildScene(parser);

    std::cout << "Lancement du rendu..." << std::endl;
    RayTracer::PpmViewer viewer("", width, height);
    viewer.start_rendering(&raytracer);
    raytracer.start_rendering();
    while (raytracer.isRenderingActive() && raytracer.getCurrentLine() < height) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::string outputFile = "output.ppm";
    std::cout << "Sauvegarde de l'image dans " << outputFile << std::endl;
    raytracer.saveImage(outputFile);
    std::cout << "Rendu terminé !" << std::endl;
    while (viewer.isDisplayActive()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}