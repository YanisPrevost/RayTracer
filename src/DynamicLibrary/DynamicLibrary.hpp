/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** dynamicLibrary
*/

#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <dlfcn.h>

namespace RayTracer {

    class DynamicLibrary {
        public:

            DynamicLibrary(std::string libName);
            ~DynamicLibrary();

            template <typename Module, typename ...Args>
            using ConstructorFunction = std::unique_ptr<Module> (*)(Args...);

            template <typename Module, typename ...Args>
            ConstructorFunction<Module, Args...> getConstructor(std::string functionName)
            {
                void (*symbol)() = (void (*)())dlsym(this->library, functionName.c_str());

                if (!symbol)
                    throw (DynamicLibraryError("Unable to find symbol: " + std::string(dlerror())));
                std::unique_ptr<Module> (*constructor)(Args...) = reinterpret_cast<std::unique_ptr<Module>(*)(Args...)> (symbol);
                return constructor;
            }

            template <typename Module, typename... Args>
            std::unique_ptr<Module> getModule(std::string functionName, Args&&... args);

            std::string getName(std::string functionName);

            void changeLibrary(std::string library);

        private:
            class DynamicLibraryError : public std::exception {
                public:
                    DynamicLibraryError(const std::string message) : msg(message) {}
                    const char* what() const noexcept override {
                        return msg.c_str();
                    }
                private:
                    std::string msg;
            };
            void *library;
            std::string _name = "";
    };
}
