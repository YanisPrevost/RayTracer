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
#include "IPrimitive.hpp"
#include "ILights.hpp"
#include "../Parsing/Parsing_cfg.hpp"
#include "../DynamicLibrary/DynamicLibrary.hpp"

namespace RayTracer {

    class RayCaster {
        private:
            Camera _camera;
            Screen _screen;
            std::vector<std::unique_ptr<IPrimitive>> _primitives;
            std::vector<std::unique_ptr<ILights>> _lights;
            std::map<std::string, std::unique_ptr<DynamicLibrary>> libraryHandles;
            std::map<std::string, std::unique_ptr<DynamicLibrary>> lightLibraries;
            int maxDepth;
            int samplesPerPixel;
            Math::Vector3D backgroundColor;
            // Trgead
            std::mutex renderMutex;
            std::atomic<bool> renderingActive;
            std::atomic<int> currentLine;
            std::condition_variable renderUpdate;
            class RayTracerError : public std::exception {
                public:
                    RayTracerError(const std::string message) : msg(message) {}
                    const char* what() const noexcept override {
                        return msg.c_str();
                    }
                private:
                    std::string msg;
            };

        public:
            RayCaster(Camera camera, Screen screen);
            ~RayCaster();

            void setCamera(const Camera& camera);
            void setResolution(int width, int height);
            void setMaxDepth(int depth) { maxDepth = depth; }
            void setSamplesPerPixel(int samples) { samplesPerPixel = samples; }
            void setBackgroundColor(const Math::Vector3D& color) { backgroundColor = color; }

            bool loadPrimitiveLibrary();
            void loadLightLibrary();
            void clearPrimitives();
            void clearLights();
            Math::Vector3D renderPixel(int x, int y);

            std::unique_ptr<DynamicLibrary> &getCurrentLibrary(std::string libName, std::string functionName);
            std::unique_ptr<DynamicLibrary> &getCurrentLightLibrary(std::string libName, std::string functionName);
            void BuildScene(const Parsing_cfg& parser);

            void start_rendering();
            void stopRendering();
            bool isRaytracingDone() const { return !(renderingActive && getCurrentLine() < _screen.getHeight()); }
            bool isRenderingActive() const { return renderingActive; }
            int getCurrentLine() const { return currentLine; }
            void waitForUpdate(int& lastLine);
            void renderLines(int startLine, int endLine);
            void renderLoop();

            const std::vector<std::unique_ptr<IPrimitive>>& getPrimitives() const {return _primitives; }

            Math::Vector3D trace_ray(const Ray& ray, int depth);
            bool saveImage(const std::string& filename) const;
            const Screen& getScreen() const { return _screen; }
    };

}

