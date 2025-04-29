/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** RayTracer.cpp
*/

#include "RayTracer.hpp"
#include <iostream>
#include <thread>
// #include <dlfcn.h>
#include "../DynamicLibrary/DynamicLibrary.hpp"
#include "../Lights/PointLight/PointLight.hpp"
// #include "Parsing/Parsing_cfg.hpp"

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

    bool RayTracer::loadPrimitiveLibrary(const std::string& libPath, const std::string& name)
    {
        std::string fullPath = libPath;

        libraryHandles[name] = std::make_unique<DynamicLibrary>(fullPath);
        std::cout << "Bibliothèque " << name << " chargée avec succès." << std::endl;
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

    Math::Vector3D RayTracer::trace_ray(const Ray& ray, int depth) const
    {
        if (depth <= 0) {
            return backgroundColor;
        }
        HitInfo closestHit = find_intersection(ray);
        if (!closestHit.hit) {
            return backgroundColor;
        }
        // Lumiere Temporaiare
        // PointLight light = PointLight(Math::Point3D(20, -20, 0), Math::Vector3D(1, 1, 1), 0.0);
        // PointLight light2 = PointLight(Math::Point3D(20, 0, 3), Math::Vector3D(0, 1, 1), 0.1);
        // Math::Vector3D color1 = light.computeDiffuseLightingColor(closestHit);
        // Math::Vector3D color2 = light2.computeDiffuseLightingColor(closestHit);
        Math::Vector3D color; //= closestHit.color; //color1 + color2;//closestHit.color;
        for (const auto &light : lights) {
            Math::Vector3D lightColor = light->computeDiffuseLightingColor(closestHit);
            color += lightColor;
        }
        // Lumiere Temporaire
        if (closestHit.reflection > 0 && depth > 1) {
            Math::Vector3D reflectDir = ray.direction - closestHit.normal * 2 * ray.direction.dot(closestHit.normal);
            reflectDir = reflectDir.normalize();
            Ray reflectRay(closestHit.point + reflectDir * 0.001, reflectDir);
            Math::Vector3D reflectColor = trace_ray(reflectRay, depth - 1);
            color = color * (1 - closestHit.reflection) + reflectColor * closestHit.reflection;
        }
        return color;
    }

    HitInfo RayTracer::find_intersection(const Ray& ray) const
    {
        HitInfo closestHit;

        closestHit.hit = false;
        closestHit.distance = std::numeric_limits<double>::max();
        for (const auto& primitive : primitives) {
            HitInfo hitInfo = primitive->intersect(ray);
            if (hitInfo.hit && hitInfo.distance < closestHit.distance) {
                closestHit = hitInfo;
            }
        }
        return closestHit;
    }

    bool RayTracer::saveImage(const std::string& filename) const
    {
        return screen.saveToPPM(filename);
    }

    void RayTracer::BuildScene(const Parsing_cfg& parser)
    {
        const std::vector<Sphere_info>& sphereInfos = parser.getSphereInfos();
        for (const auto& sphereInfo : sphereInfos) {
            std::vector<double> params = {
                sphereInfo.getPosition().X, sphereInfo.getPosition().Y, sphereInfo.getPosition().Z,
                sphereInfo.getRadius(),
                sphereInfo.getR() / 255.0, sphereInfo.getG() / 255.0, sphereInfo.getB() / 255.0
            };
            addPrimitive("Sphere", params);
        }
        // this->lights.push_back(std::make_unique<PointLight>(Math::Point3D(50, -20, 10), Math::Vector3D(1, 1, 1), 1));
        this->lights.push_back(std::make_unique<PointLight>(Math::Point3D(0, 30, 10), Math::Vector3D(1, 1.0, 1), 1));
        // this->lights.push_back(std::make_unique<PointLight>(Math::Point3D(-20, 10, 0), Math::Vector3D(1, 1, 1), 0.5));
    }

}
