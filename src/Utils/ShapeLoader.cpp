/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShapeLoader.cpp
*/

#include "ShapeLoader.hpp"

namespace RayTracer {

    ShapeLoader::~ShapeLoader() {}

    bool ShapeLoader::loadShapeLibrary(const std::string& libraryPath) {
        void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Erreur lors du chargement de la bibliothèque " << libraryPath << ": " << dlerror() << std::endl;
            return false;
        }
        create_shape_t createShape = (create_shape_t)dlsym(handle, "create_shape");
        if (!createShape) {
            std::cerr << "Erreur lors de la récupération de la fonction create_shape: " << dlerror() << std::endl;
            dlclose(handle);
            return false;
        }
        IShape* shape = createShape();
        if (!shape) {
            std::cerr << "La fonction create_shape n'a pas retourné d'instance valide." << std::endl;
            dlclose(handle);
            return false;
        }
        loadedLibraries.push_back(std::make_unique<LibraryHandle>(handle, libraryPath));
        shapes.push_back(std::unique_ptr<IShape>(shape));
        std::cout << "Forme chargée avec succès: " << shape->getType() << " depuis " << libraryPath << std::endl;
        return true;
    }

    const std::vector<std::unique_ptr<IShape>>& ShapeLoader::getShapes() const {
        return shapes;
    }
}
