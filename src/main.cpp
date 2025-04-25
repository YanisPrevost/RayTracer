/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** main.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include "Scene/Scene.hpp"
#include "Utils/utils.hpp"
#include "Visualization/PpmViewer.hpp"
#include "Parsing/Parsing_cfg.hpp"

void rayTracingThread(int width, int height, const RayTracer::Scene& scene)
{
    RayTracer::Utils::init_ppm_file(width, height);
    const RayTracer::Camera& cam = scene.getCamera();

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = static_cast<double>(i) / (width - 1);
            double v = static_cast<double>(j) / (height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            Math::Vector3D color;
            scene.trace(r, color);
            RayTracer::Utils::write_color(color);
        }
    }
    RayTracer::Utils::finalize_ppm_file();
    std::cerr << "Génération d'image terminée.\n";
}

void displayThread()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    sf::RenderWindow window(sf::VideoMode(RayTracer::Utils::imageWidth, RayTracer::Utils::imageHeight), "RayTracer Visualisation");
    sf::Texture texture;
    sf::Sprite sprite;
    const auto refreshRate = std::chrono::milliseconds(50);
    auto lastRefresh = std::chrono::steady_clock::now();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        auto now = std::chrono::steady_clock::now();
        if (now - lastRefresh >= refreshRate) {
            lastRefresh = now;
            RayTracer::PpmViewer viewer;
            {
                std::lock_guard<std::mutex> lock(RayTracer::Utils::ppmFileMutex);
                if (!RayTracer::Utils::ppmHeaderWritten)
                    continue;
            }
            if (viewer.loadFromFile("output.ppm")) {
                const auto& sfImage = viewer.getImage();
                texture.loadFromImage(sfImage);
                sprite.setTexture(texture, true);
                window.clear();
                window.draw(sprite);
                window.display();
                int totalPixels = RayTracer::Utils::imageWidth * RayTracer::Utils::imageHeight;
                if (RayTracer::Utils::completedPixels >= totalPixels) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
            }
        }
    }
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config_file>" << std::endl;
        return 84;
    }
    RayTracer::Parsing_cfg info(argv[1]);
    info.parse();

    RayTracer::Scene scene(info);

    int width = info.getCamInfo().getWidth();
    int height = info.getCamInfo().getHeight();

    std::thread tracingThread(rayTracingThread, width, height, std::cref(scene));
    std::thread sfmlThread(displayThread);

    tracingThread.join();
    if (sfmlThread.joinable()) {
        sfmlThread.join();
    }

    return 0;
}