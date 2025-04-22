/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShapeLoader.hpp
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <dlfcn.h>
#include <iostream>
#include "../Interfaces/IShape.hpp"

namespace RayTracer {
    class ShapeLoader {
    private:
        class LibraryHandle {
            public:
                void* handle;
                std::string path;
                LibraryHandle(void* handle, const std::string& path) : handle(handle), path(path) {}
                ~LibraryHandle() {
                    if (handle) {
                        dlclose(handle);
                    }
                }
            };
        std::vector<std::unique_ptr<LibraryHandle>> loadedLibraries;
        std::vector<std::unique_ptr<IShape>> shapes;
    public:
        ~ShapeLoader();
        bool loadShapeLibrary(const std::string& libraryPath);
        const std::vector<std::unique_ptr<IShape>>& getShapes() const;
    };
}
