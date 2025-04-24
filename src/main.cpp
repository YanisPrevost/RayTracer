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
#include "Builders/ShapeBuilder.hpp"
#include "Builders/Sphere/SphereBuilder.hpp"
#include "Utils/utils.hpp"
#include "Visualization/PpmViewer.hpp"
#include "Decorator/ShapeDecorator.hpp"
#include "Parsing/Parsing_cfg.hpp"
#include <cstring>

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
            const RayTracer::IShape* hitShape = nullptr;
            for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
                const auto& shape = *it;
                if (shape && shape->hits(r)) {
                    hit = true;
                    hitShape = shape.get();
                    break;
                }
            }
            Math::Vector3D color;
            if (hit) {
                if (hitShape && strcmp(hitShape->getType(), "ColoredShape") == 0) {
                    const RayTracer::ColoredShape* coloredShape = dynamic_cast<const RayTracer::ColoredShape*>(hitShape);
                    if (coloredShape) {
                        color = Math::Vector3D( coloredShape->getRed() / 255.0, coloredShape->getGreen() / 255.0, coloredShape->getBlue() / 255.0
                        );
                    } else {
                        color = Math::Vector3D(1.0, 0.0, 0.0);
                    }
                }
            }
            else
                color = Math::Vector3D(0.5, 0.7, 1.0); // Couleur d'arrière-plan
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
    RayTracer::Parsing_cfg info(argv[1]);
    info.parse();

    std::vector<std::unique_ptr<RayTracer::IShape>> shapes;
    RayTracer::SphereBuilder sphereBuilder;
    RayTracer::ShapeDirector director;
    int width = info.getCamInfo().getWidth();
    int height = info.getCamInfo().getHeight();

    RayTracer::Camera cam(info.getCamInfo().getPosition(), info.getCamInfo().getFov(), width, height);

    for (const auto& sphereInfo : info.getSphereInfos()) {
        sphereBuilder.reset();
        sphereBuilder.setPosition(sphereInfo.getPosition());
        sphereBuilder.setRadius(sphereInfo.getRadius());
        sphereBuilder.setColor(sphereInfo.getR(), sphereInfo.getG(), sphereInfo.getB());
        shapes.push_back(director.createSphere(sphereBuilder, sphereInfo.getPosition()));
    }

    std::thread tracingThread(rayTracingThread, width, height, std::cref(cam), std::cref(shapes));
    std::thread sfmlThread(displayThread);

    tracingThread.join();
    if (sfmlThread.joinable()) {
        sfmlThread.join();
    }
    return 0;
}