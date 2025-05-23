/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** RayTracerApp
*/

#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>
#include <memory>
#include <filesystem>
#include "../Builder/RayTracer.hpp"
#include "../Visualization/PpmViewer.hpp"
#include "../Parsing/Parsing_cfg.hpp"
#include "Scene.hpp"
#include <optional>
#include "../Builder/LibraryManager.hpp"
// #include "../Builder/Scene.hpp"

namespace RayTracer {

    class RayTracerApp {
        public:
            RayTracerApp(std::string configFile) : _configFile(configFile) {};
            ~RayTracerApp();
            void run();
            void displayTime();
            void loadConfigFile();
            std::unique_ptr<RayCaster> &getRayCaster() { return _raycaster; }
            std::unique_ptr<PpmViewer> &getViewer() { return _viewer; }
            std::shared_ptr<Scene> &getScene() { return _scene; }
            LibraryManager &getLibraryHandles() { return _libraryHandles; }
        private:
            std::string _configFile;
            std::chrono::_V2::system_clock::time_point beginingTime;
            LibraryManager _libraryHandles;
            std::unique_ptr<RayCaster> _raycaster;
            std::unique_ptr<PpmViewer> _viewer;
            std::shared_ptr<Scene> _scene;
            std::optional<Parsing_cfg> _parser;
            std::filesystem::file_time_type currentWriteTime;
    };

}