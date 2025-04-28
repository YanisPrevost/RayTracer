/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** RayTracer.cpp
*/

#include "RayTracer.hpp"
#include <iostream>
#include <thread>
#include <dlfcn.h>

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
        for (auto& handle : libraryHandles) {
            if (handle.second) {
                dlclose(handle.second);
            }
        }
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

        void *handle = dlopen(fullPath.c_str(), RTLD_LAZY);

        libraryHandles[name] = handle;
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

        IPrimitive* (*createFunc)() = reinterpret_cast<IPrimitive* (*)()>(dlsym(it->second, "createPrimitive"));
        IPrimitive* primitive = createFunc();
        if (primitive) {
            std::unique_ptr<IPrimitive> configuredPrimitive = primitive->create(params);
            delete primitive;
            if (configuredPrimitive) {
                primitives.push_back(std::move(configuredPrimitive));
                std::cout << "Primitive " << type << " ajoutée avec succès." << std::endl;
                return true;
            }
        }
        return false;
    }

    void RayTracer::clearPrimitives()
    {
        primitives.clear();
    }

    void RayTracer::render()
    {
        start_rendering();

        int lastLine = 0;
        int height = screen.getHeight();
        while (isRenderingActive() && currentLine < height) {
            waitForUpdate(lastLine);
        }
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
        renderingActive.store(false);
        renderUpdate.notify_all();
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
        renderingActive.store(false);
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
        Math::Vector3D color = closestHit.color;
        double lightIntensity = std::max(0.0, closestHit.normal.dot(Math::Vector3D(0, 1, 0)));
        color = color * lightIntensity;
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

}
