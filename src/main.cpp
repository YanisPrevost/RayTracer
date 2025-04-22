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
#include "Camera/Camera.hpp"
#include "Utils/ShapeLoader.hpp"
#include "Utils/utils.hpp"
#include "Visualization/PpmViewer.hpp"

void rayTracingThread(int width, int height, const RayTracer::Camera& cam,
        const std::vector<std::unique_ptr<RayTracer::IShape>>& shapes)
{
    RayTracer::Utils::init_ppm_file(width, height);
    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = static_cast<double>(i) / (width - 1);
            double v = static_cast<double>(j) / (height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            bool hit = false;
            for (const auto& shape : shapes) {
                if (shape && shape->hits(r)) {
                    hit = true;
                    break;
                }
            }
            Math::Vector3D color;
            if (hit)
                color = Math::Vector3D(1.0, 0.0, 0.0); // Red if hit
            else
                color = Math::Vector3D(0.5, 0.7, 1.0); // Bg color
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

int main() {
    const int width = 1280;
    const int height = 720;
    RayTracer::Camera cam;
    RayTracer::ShapeLoader shapeLoader;

    std::cout << "Chargement des formes..." << std::endl;
    if (!shapeLoader.loadShapeLibrary("./Plugins/Primitives/libsphere.so")) {
        std::cout << "Impossible de charger la sphère." << std::endl;
        return 1;
    }
    const auto& shapes = shapeLoader.getShapes();
    if (shapes.empty()) {
        std::cout << "Aucune forme n'a été chargée." << std::endl;
        return 1;
    }
    std::cout << "Nombre de formes chargées: " << shapes.size() << std::endl;
    for (const auto& shape : shapes) {
        std::cout << "Type de forme: " << (shape ? shape->getType() : "null") << std::endl;
    }
    std::thread tracingThread(rayTracingThread, width, height, std::cref(cam), std::cref(shapes));
    std::thread sfmlThread(displayThread);
    tracingThread.join();
    if (sfmlThread.joinable()) {
        sfmlThread.join();
    }
    return 0;
}