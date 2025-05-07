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
#include "ILights.hpp"
#include <filesystem>
#include "../Parsing/ArgumentMap.hpp"

namespace RayTracer {

    RayCaster::RayCaster(Camera camera, Screen screen)
        : _screen(screen), maxDepth(5), samplesPerPixel(1), backgroundColor(0.2, 0.2, 0.2),
          renderingActive(false), currentLine(0), _camera(camera)
    {
        loadPrimitiveLibrary();
        loadLightLibrary();
    }

    RayCaster::~RayCaster()
    {
        stopRendering();
        _primitives.clear();
        _lights.clear();
        libraryHandles.clear();
    }

    void RayCaster::setCamera(const Camera& camera)
    {
        this->_camera = camera;
    }

    void RayCaster::setResolution(int width, int height)
    {
        _screen = Screen(width, height);
    }

    bool RayCaster::loadPrimitiveLibrary()
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

    void RayCaster::loadLightLibrary()
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

    void RayCaster::start_rendering()
    {
        if (renderingActive.load()) {
            return;
        }
        currentLine.store(0);
        renderingActive.store(true);
        std::thread renderThread(&RayCaster::renderLoop, this);
        renderThread.detach();
    }

    void RayCaster::stopRendering()
    {
        if (!renderingActive.load())
            return;
        renderingActive.store(false);
        renderUpdate.notify_all();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    void RayCaster::waitForUpdate(int& lastLine)
    {
        std::unique_lock<std::mutex> lock(renderMutex);
        renderUpdate.wait_for(lock, std::chrono::milliseconds(100), [&]() {
            return _screen.getCompletedLines()[lastLine] || !renderingActive.load();
        });
        lastLine++;
        // lastLine = currentLine;
    }

    Math::Vector3D RayCaster::renderPixel(int x, int y)
    {
        Math::Vector3D color(0, 0, 0);
        double u, v;
        _screen.getUV(x, y, u, v);
        for (int s = 0; s < samplesPerPixel; s++) {
            if (samplesPerPixel > 1) {
                double du = 1.0 / _screen.getWidth();
                double dv = 1.0 / _screen.getHeight();
                u += du * (rand() / static_cast<double>(RAND_MAX) - 0.5);
                v += dv * (rand() / static_cast<double>(RAND_MAX) - 0.5);
            }
            Ray ray = _camera.generate_ray(u, v);
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
        return color;
    }

    void RayCaster::renderLine(int y)
    {
        int width = _screen.getWidth();
        std::vector<Math::Vector3D> lineColors(width);
        for (int x = 0; x < width && renderingActive.load(); x++) {
            Math::Vector3D color = renderPixel(x, y);
            lineColors[x] = color;
        }
        {
            std::lock_guard<std::mutex> lock(screenMutex);
            for (int x = 0; x < width; x++) {
                _screen.setPixel(x, y, lineColors[x]);
            }
            // currentLine++;
            _screen.setLineCompleted(y);
        }
        // {
        //     std::unique_lock<std::mutex> lock(currentLineMutex);
        //     currentLineCV.wait(lock, [&]() {
        //         return currentLine == y;
        //     });
        //     currentLine.store(y + 1);
        // }
        // currentLineCV.notify_all();
    }

    void RayCaster::renderLines()
    {
        int y;
        int height = _screen.getHeight();
    
        while ((y = lineToRender.fetch_add(1)) < height) {
            renderLine(y);
        }
    }

    // void RayCaster::renderLines(int startLine, int endLine)
    // {
    //     int height = _screen.getHeight();

    //     for (int y = startLine; y < endLine && y < height && renderingActive.load(); y++) {
    //         renderLine(y);
    //     }
    //     renderUpdate.notify_all();
    // }

    void RayCaster::renderLoop()
    {
        lineToRender.store(0);

        std::vector<std::thread> threads;
        int numThreads = std::thread::hardware_concurrency() - 2;

        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(&RayCaster::renderLines, this);
        }

        for (auto& t : threads) {
            t.join();
        }
        renderUpdate.notify_all();
    }

    Math::Vector3D RayCaster::trace_ray(const Ray& ray, int depth)
    {
        if (depth <= 0) {
            return backgroundColor;
        }
        HitInfo closestHit = ray.find_intersection(_primitives);
        if (!closestHit.hit) {
            return backgroundColor;
        }
        float diffusionLight = 0.1;
        Math::Vector3D color = (closestHit.color * diffusionLight);
        for (const auto &light : _lights) {
            Math::Vector3D lightColor = light->computeLightingColor(closestHit, *this);
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

    bool RayCaster::saveImage(const std::string& filename) const
    {
        std::cout << "Saving image in " << filename << std::endl;
        return _screen.saveToPPM(filename);
        std::cout << "Rendering done !" << std::endl;
    }

    std::unique_ptr<DynamicLibrary> &RayCaster::getCurrentLibrary(std::string libName, std::string functionName)
    {
        for (auto &lib : libraryHandles) {
            if (libName == lib.second->getName(functionName)) {
                std::unique_ptr<DynamicLibrary> &library = lib.second;
                return library;
            }
        }
        throw (RayTracerError("Couldn't find primitive" + libName));
    }

    std::unique_ptr<DynamicLibrary> &RayCaster::getCurrentLightLibrary(std::string libName, std::string functionName)
    {
        for (auto &lib : lightLibraries) {
            if (libName == lib.second->getName(functionName)) {
                std::unique_ptr<DynamicLibrary> &library = lib.second;
                return library;
            }
        }
        throw RayTracerError("Couldn't find light " + libName);
    }

    void RayCaster::BuildScene(const Parsing_cfg& parser)
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
