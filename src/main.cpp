#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <cstring>
#include <thread>
#include <chrono>
#include <dlfcn.h>
#include "Parsing/Parsing_cfg.hpp"
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

    std::vector<std::string> primitiveTypes = {"Sphere"};

    const RayTracer::Cam_info& camInfo = parser.getCamInfo();
    RayTracer::RayTracer raytracer(camInfo.getWidth(), camInfo.getHeight());
    RayTracer::Camera camera(
        camInfo.getPosition(),
        Math::Vector3D(0, 0, -1),
        Math::Vector3D(0, 1, 0),
        camInfo.getFov()
    );
    raytracer.setCamera(camera);
    for (const auto& type : primitiveTypes) {
        std::string libPath = "./Plugins/Primitives/lib" + type + ".so";
        raytracer.loadPrimitiveLibrary(libPath, type);
    }
    const std::vector<RayTracer::Sphere_info>& sphereInfos = parser.getSphereInfos();
    for (const auto& sphereInfo : sphereInfos) {
        std::vector<double> params = {
            sphereInfo.getPosition().X, sphereInfo.getPosition().Y, sphereInfo.getPosition().Z,
            sphereInfo.getRadius(),
            sphereInfo.getR() / 255.0, sphereInfo.getG() / 255.0, sphereInfo.getB() / 255.0
        };
        raytracer.addPrimitive("Sphere", params);
    }

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