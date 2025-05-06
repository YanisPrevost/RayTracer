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
#include "Builder/RayTracer.hpp"
#include "Visualization/PpmViewer.hpp"
#include "../Rectangle3D/Screen.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file.cfg>" << std::endl;
        return 1;
    }
    try {
        std::string configFile = argv[1];
        RayTracer::Parsing_cfg parser(configFile);

        RayTracer::RayCaster raycaster(
            RayTracer::Camera(parser.getCamInfo()),
            RayTracer::Screen(parser.getCamInfo()["resolution"].as<RayTracer::ArgumentMap>())
        );
        raycaster.BuildScene(parser);

        RayTracer::PpmViewer viewer("", raycaster, raycaster.getScreen().getWidth(), raycaster.getScreen().getHeight());
        viewer.start_rendering();
        raycaster.start_rendering();
        while (!raycaster.isRaytracingDone()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::string outputFile = "output.ppm";
        raycaster.saveImage(outputFile);
        while (viewer.isDisplayActive()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}