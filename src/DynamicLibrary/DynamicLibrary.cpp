/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** dynamicLibrary
*/
#include "DynamicLibrary.hpp"
#include <dlfcn.h>

RayTracer::DynamicLibrary::DynamicLibrary(std::string libName)
{
    this->library = dlopen(libName.c_str(), RTLD_LAZY);
    if (!this->library)
        throw DynamicLibraryError("Unable to open library: " + std::string(dlerror()));
}

RayTracer::DynamicLibrary::~DynamicLibrary()
{
    dlclose(this->library);
}

void RayTracer::DynamicLibrary::changeLibrary(std::string libraryName)
{
    dlclose(this->library);
    this->library = dlopen(libraryName.c_str(), RTLD_LAZY);
    if (!this->library)
        throw DynamicLibraryError("Unable to open library: " + std::string(dlerror()));
}
