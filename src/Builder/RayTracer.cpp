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
#include "../Parsing/ArgumentMap.hpp"

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

    void RayTracer::loadLightLibrary()
    {
        std::filesystem::path libPath = "Plugins/Lights/";

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
                lightLibraries[typeName] = std::make_unique<DynamicLibrary>(libPath / libName);
            }
        }
    }

    void RayTracer::clearPrimitives()
    {
        _primitives.clear();
    }

    void RayTracer::clearLights()
    {
        _lights.clear();
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
        HitInfo closestHit = ray.find_intersection(_primitives);
        if (!closestHit.hit) {
            return backgroundColor;
        }
        Math::Vector3D color(0, 0, 0);
        for (const auto &light : _lights) {
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

    std::unique_ptr<DynamicLibrary> &RayTracer::getCurrentLibrary(std::string libName, std::string functionName)
    {
        for (auto &lib : libraryHandles) {
            if (libName == lib.second->getName(functionName)) {
                std::unique_ptr<DynamicLibrary> &library = lib.second;
                return library;
            }
        }
        throw std::runtime_error("Couldn't find primitive" + libName);
    }

    std::unique_ptr<DynamicLibrary> &RayTracer::getCurrentLightLibrary(std::string libName, std::string functionName)
    {
        for (auto &lib : lightLibraries) {
            if (libName == lib.second->getName(functionName)) {
                std::unique_ptr<DynamicLibrary> &library = lib.second;
                return library;
            }
        }
        throw std::runtime_error("Couldn't find light " + libName);
    }

    void RayTracer::BuildScene(const Parsing_cfg& parser)
    {
        _primitives.clear();
        const std::unordered_map<std::string, std::vector<ArgumentMap>> &primitivesInfo = parser.getPrimitiveInfo();
        for (const auto &primitive : primitivesInfo) {
            std::unique_ptr<DynamicLibrary> &currentPrimitive = getCurrentLibrary(primitive.first, "getPrimitiveName");

            auto constructor = currentPrimitive->getConstructor<IPrimitive, ArgumentMap>("createPrimitive");

            for (auto params : primitive.second) {
                _primitives.push_back(constructor(params));
            }
        }

        const std::unordered_map<std::string, std::vector<ArgumentMap>> &lightsInfo = parser.getLightsInfo();
        for (const auto &light : lightsInfo) {
            std::unique_ptr<DynamicLibrary> &currentLight = getCurrentLightLibrary(light.first, "getLightName");

            auto constructor = currentLight->getConstructor<ILights, ArgumentMap>("createLight");

            for (auto params : light.second) {
                _lights.push_back(constructor(params));
            }
        }
    }
}
