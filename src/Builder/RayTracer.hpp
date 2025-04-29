/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** RayTracer.hpp
*/

#pragma once
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "../Camera/Camera.hpp"
#include "../Rectangle3D/Screen.hpp"
#include "../Interfaces/IPrimitive.hpp"
#include "../Interfaces/ILights.hpp"
#include "../Parsing/Parsing_cfg.hpp"
#include "../DynamicLibrary/DynamicLibrary.hpp"

namespace RayTracer {

    class RayTracer {
        private:
            Camera camera;
            Screen screen;
            std::vector<std::unique_ptr<IPrimitive>> primitives;
            std::vector<std::unique_ptr<ILights>> lights;
            std::map<std::string, std::unique_ptr<DynamicLibrary>> libraryHandles;
            int maxDepth;
            int samplesPerPixel;
            Math::Vector3D backgroundColor;
            // Trgead
            std::mutex renderMutex;
            std::atomic<bool> renderingActive;
            std::atomic<int> currentLine;
            std::condition_variable renderUpdate;

        public:
            RayTracer(int width = 800, int height = 600);
            ~RayTracer();

            void setCamera(const Camera& camera);
            void setResolution(int width, int height);
            void setMaxDepth(int depth) { maxDepth = depth; }
            void setSamplesPerPixel(int samples) { samplesPerPixel = samples; }
            void setBackgroundColor(const Math::Vector3D& color) { backgroundColor = color; }

            bool loadPrimitiveLibrary(const std::string& libPath, const std::string& name);
            bool addPrimitive(const std::string& type, const std::vector<double>& params);
            void clearPrimitives();

            void BuildScene(const Parsing_cfg& parser);

            void start_rendering();
            void stopRendering();
            bool isRenderingActive() const { return renderingActive; }
            int getCurrentLine() const { return currentLine; }
            void waitForUpdate(int& lastLine);
            void renderLines(int startLine, int endLine);
            void renderLoop();

            Math::Vector3D trace_ray(const Ray& ray, int depth) const;
            HitInfo find_intersection(const Ray& ray) const;

            bool saveImage(const std::string& filename) const;
            const Screen& getScreen() const { return screen; }
    };

}

