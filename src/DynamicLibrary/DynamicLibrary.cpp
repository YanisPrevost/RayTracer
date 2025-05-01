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

std::string RayTracer::DynamicLibrary::getName(std::string functionName)
{
    if (_name == "") {
        char *(*symbol)() = (char *(*)())dlsym(this->library, functionName.c_str());
        if (!symbol)
            throw (DynamicLibraryError("Unable to find symbol: " + std::string(dlerror())));
        char *name = symbol();
        std::string resName = std::string(name);
        _name = resName;
    }
    return _name;
}

template <typename Module, typename... Args>
std::unique_ptr<Module> RayTracer::DynamicLibrary::getModule(std::string functionName, Args&&... args)
{
    void (*symbol)() = (void (*)())dlsym(this->library, functionName.c_str());

    if (!symbol)
        throw (DynamicLibraryError("Unable to find symbol: " + std::string(dlerror())));
    std::unique_ptr<Module> (*constructor)(Args...) = reinterpret_cast<std::unique_ptr<Module>(*)(Args...)> (symbol);

    if (!constructor)
        throw(DynamicLibraryError("Wrongly Formatted Module: "));
    std::unique_ptr<Module> res = constructor(std::forward<Args>(args)...);
    return res;
}

// template <typename Module, typename ...Args>
// using ConstructorFunction = std::unique_ptr<Module> (*)(Args);

