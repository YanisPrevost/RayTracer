/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** RayTracer.cpp
*/

#include "RayTracer.hpp"
#include <iostream>
#include <thread>
#include "../DynamicLibrary/DynamicLibrary.hpp"
#include "../Lights/PointLight/PointLight.hpp"
#include "../Lights/DirectionalLight/DirectionalLight.hpp"
#include "../Interfaces/ILights.hpp"
#include <filesystem>

namespace RayTracer {

    RayTracer::RayTracer(int width, int height)
        : screen(width, height), maxDepth(5), samplesPerPixel(1), backgroundColor(0.2, 0.2, 0.2),
          renderingActive(false), currentLine(0)
    {
    }

    RayTracer::~RayTracer()
    {
        stopRendering();
        clearPrimitives();
        clearLights();
        libraryHandles.clear();
    }

    void RayTracer::setCamera(const Camera& camera)
    {
        this->camera = camera;
    }

    void RayTracer::setResolution(int width, int height)
    {
        screen = Screen(width, height);
    }

    bool RayTracer::loadPrimitiveLibrary()
    {
        std::filesystem::path libPath = "Plugins/Primitives/";

        for (const auto& entry : std::filesystem::directory_iterator(libPath)) {
            if (entry.path().extension() == ".so") {
                std::string libName = entry.path().filename().string();
                std::cout << "Chargement de la bibliothèque: " << libName << std::endl;
                std::string typeName = libName;
                if (typeName.substr(0, 3) == "lib") {
                    typeName = typeName.substr(3);
                }
                if (typeName.size() > 3 && typeName.substr(typeName.size() - 3) == ".so") {
                    typeName = typeName.substr(0, typeName.size() - 3);
                }
                libraryHandles[typeName] = std::make_unique<DynamicLibrary>(libPath / libName);
            }
        }
        return true;
    }

    bool RayTracer::addPrimitive(const std::string& type, const std::vector<double>& params)
    {
        auto it = libraryHandles.find(type);
        if (it == libraryHandles.end()) {
            std::cerr << "Type de primitive inconnu: " << type << std::endl;
            return false;
        }

        std::unique_ptr<IPrimitive> configuredPrimitive = it->second->getModule<IPrimitive>("createPrimitive", params);
        primitives.push_back(std::move(configuredPrimitive));
        std::cout << "Primitive " << type << " ajoutée avec succès." << std::endl;
        return true;
    }

    void RayTracer::clearPrimitives()
    {
        primitives.clear();
    }

    void RayTracer::clearLights()
    {
        lights.clear();
    }

    bool RayTracer::AddPointLights(const Light_Point& lightInfo)
    {
        // lights.push_back(std::make_unique<PointLight>(
        //     Math::Point3D(lightInfo.getPosition().X, lightInfo.getPosition().Y, lightInfo.getPosition().Z),
        //     Math::Vector3D(lightInfo.getR() / 255.0, lightInfo.getG() / 255.0, lightInfo.getB() / 255.0),
        //     lightInfo.getDiffuse()
        // ));
        lights.push_back(std::make_unique<DirectionalLight>(
            Math::Point3D(lightInfo.getPosition().X, lightInfo.getPosition().Y, lightInfo.getPosition().Z),
            Math::Vector3D(lightInfo.getR() / 255.0, lightInfo.getG() / 255.0, lightInfo.getB() / 255.0),
            lightInfo.getDiffuse()
        ));
        std::cout << "Lumière ponctuelle ajoutée avec succès." << std::endl;
        return true;
    }

    void RayTracer::start_rendering()
    {
        if (renderingActive.load()) {
            return;
        }
        currentLine.store(0);
        renderingActive.store(true);
        std::thread renderThread(&RayTracer::renderLoop, this);
        renderThread.detach();
    }

    void RayTracer::stopRendering()
    {
        if (!renderingActive.load())
            return;
        renderingActive.store(false);
        renderUpdate.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void RayTracer::waitForUpdate(int& lastLine)
    {
        std::unique_lock<std::mutex> lock(renderMutex);
        renderUpdate.wait_for(lock, std::chrono::milliseconds(100), [&]() {
            return currentLine > lastLine || !renderingActive.load();
        });
        lastLine = currentLine;
    }

    void RayTracer::renderLines(int startLine, int endLine)
    {
        int width = screen.getWidth();
        int height = screen.getHeight();

        for (int y = startLine; y < endLine && y < height && renderingActive.load(); y++) {
            for (int x = 0; x < width && renderingActive.load(); x++) {
                Math::Vector3D color(0, 0, 0);
                for (int s = 0; s < samplesPerPixel; s++) {
                    double u, v;
                    screen.getUV(x, y, u, v);
                    if (samplesPerPixel > 1) {
                        double du = 1.0 / width;
                        double dv = 1.0 / height;
                        u += du * (rand() / static_cast<double>(RAND_MAX) - 0.5);
                        v += dv * (rand() / static_cast<double>(RAND_MAX) - 0.5);
                    }
                    Ray ray = camera.generate_ray(u, v);
                    color += trace_ray(ray, maxDepth);
                }
                if (samplesPerPixel > 1) {
                    color = color / static_cast<double>(samplesPerPixel);
                }
                color = Math::Vector3D(
                    sqrt(color.X),
                    sqrt(color.Y),
                    sqrt(color.Z)
                );
                screen.setPixel(x, y, color);
            }
            currentLine.store(y + 1);
        }
        renderUpdate.notify_all();
    }

    void RayTracer::renderLoop()
    {
        int height = screen.getHeight();
        renderLines(0, height);
        renderUpdate.notify_all();
    }

    Math::Vector3D RayTracer::trace_ray(const Ray& ray, int depth)
    {
        if (depth <= 0) {
            return backgroundColor;
        }
        HitInfo closestHit = ray.find_intersection(primitives);
        if (!closestHit.hit) {
            return backgroundColor;
        }
        Math::Vector3D color;
        for (const auto &light : lights) {
            Math::Vector3D lightColor = light->computePointLightingColor(closestHit, *this);
            color += lightColor;
        }
        if (closestHit.reflection > 0 && depth > 1) {
            Math::Vector3D reflectDir = ray.direction - closestHit.normal * 2 * ray.direction.dot(closestHit.normal);
            reflectDir = reflectDir.normalize();
            Ray reflectRay(closestHit.point + reflectDir * 0.001, reflectDir);
            Math::Vector3D reflectColor = trace_ray(reflectRay, depth - 1);
            color = color * (1 - closestHit.reflection) + reflectColor * closestHit.reflection;
        }
        return color;
    }

    bool RayTracer::saveImage(const std::string& filename) const
    {
        return screen.saveToPPM(filename);
    }

    void RayTracer::BuildScene(const Parsing_cfg& parser)
    {
        primitives.clear();
        const std::vector<Sphere_info>& sphereInfos = parser.getSphereInfos();
        for (const auto& sphereInfo : sphereInfos) {
            std::vector<double> params = {
                sphereInfo.getPosition().X, sphereInfo.getPosition().Y, sphereInfo.getPosition().Z,
                sphereInfo.getRadius(),
                sphereInfo.getR() / 255.0, sphereInfo.getG() / 255.0, sphereInfo.getB() / 255.0
            };
            addPrimitive("Sphere", params);
        }

        const std::vector<Plane_info>& planeInfos = parser.getPlaneInfos();
        for (const auto& planeInfo : planeInfos) {
            int axisValue = 2;
            if (planeInfo.getPosition().X != 0) {
                axisValue = 0;
            } else if (planeInfo.getPosition().Y != 0) {
                axisValue = 1;
            }
            double position = 0;
            switch (axisValue) {
                case 0: position = planeInfo.getPosition().X; break;
                case 1: position = planeInfo.getPosition().Y; break;
                case 2: position = planeInfo.getPosition().Z; break;
            }
            std::vector<double> params = {
                static_cast<double>(axisValue),
                position,
                planeInfo.getR() / 255.0, planeInfo.getG() / 255.0, planeInfo.getB() / 255.0
            };
            addPrimitive("Plane", params);
        }

        this->lights.push_back(std::make_unique<PointLight>(
            Math::Point3D(15, 10, 12),
            Math::Vector3D(1.0, 1.0, 1.0),
            1.0
        ));

        // for (const auto& Light_Info : parser.getLightPointInfos()) {
            // Light_Point lightInfo;
            // lightInfo.setPosition(Math::Point3D(4.0, 6, 4));
            // lightInfo.setColor(1.0, 1.0, 1.0);
            // lightInfo.setLightInfo(1, 1.0);
            // AddPointLights(lightInfo);
        // }
        // for (const auto& Light_Info : parser.getLightDirectionInfos()) {
        //     Light_Direction lightInfo;
        //     lightInfo.setDirection(Light_Info.getDirection());
        //     lightInfo.setColor(Light_Info.getR(), Light_Info.getG(), Light_Info.getB());
        //     lightInfo.setLightInfo(0.2, 1.0);
        //     AddPointLights(lightInfo);
        // }
    }

}
