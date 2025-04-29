/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** dynamicLibrary
*/

#ifndef DYNAMICLIBRARY_HPP_
#define DYNAMICLIBRARY_HPP_

#include <iostream>
#include <vector>
#include <memory>
#include <dlfcn.h>
namespace RayTracer {

    /**
     * @brief DynamicLibrary class
     * 
     * This class is used to manage dynamic libraries in the arcade system.
     * It provides methods to load and retrieve modules from the dynamic library.
     */
    class DynamicLibrary {
        public:
            /**
             * @brief Constructor for DynamicLibrary
             * 
             * This constructor initializes the dynamic library with the given library name.
             * It loads the library and checks for errors.
             * 
             * @param libName The name of the library to load
             * @throw DynamicLibraryError if the library cannot be loaded
             * @return void
             * @note The library name should be in the format "./lib/arcade_<library_name>.so"
             */
            DynamicLibrary(std::string libName);
            ~DynamicLibrary();

            /**
             * @brief Retrieves a module from the dynamic library
             * 
             * This function retrieves a module from the dynamic library using the provided function name.
             * It returns a unique pointer to the module.
             * 
             * @tparam Module The type of the module to retrieve
             * @param functionName The name of the function to retrieve
             * @return std::unique_ptr<Module> A unique pointer to the retrieved module
             */
            template <typename Module, typename... Args>
            std::unique_ptr<Module> getModule(std::string functionName, Args&&... args)
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

            /**
             * @brief Changes the dynamic library
             * 
             * This function changes the current dynamic library to the specified library.
             * It closes the current library and loads the new one.
             * 
             * @param library The name of the new library to load
             * @throw DynamicLibraryError if the library cannot be loaded
             * @return void
             */
            void changeLibrary(std::string library);

            private:
                /**
                 * @brief Exception class for dynamic library errors
                 * 
                 * This class is used to handle errors related to dynamic libraries.
                 * It inherits from std::exception and provides a custom error message.
                 */
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
    };
}
#endif /* !DYNAMICLIBRARY_HPP_ */
