/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PlaneBuilder.cpp
*/

#include "PlaneBuilder.hpp"

namespace RayTracer {

    std::unique_ptr<IShape> PlaneBuilder::build() {
        void* handle = dlopen("./Plugins/Primitives/libplane.so", RTLD_LAZY);
        if (!handle) {
            std::cerr << "Erreur lors du chargement de la bibliothèque: " << dlerror() << std::endl;
            return nullptr;
        }
        create_shape_t createShape = (create_shape_t)dlsym(handle, "create_shape");
        if (!createShape) {
            std::cerr << "Erreur lors de la récupération de la fonction create_shape: " << dlerror() << std::endl;
            dlclose(handle);
            return nullptr;
        }
        IShape* shape = createShape();
        if (!shape) {
            std::cerr << "La fonction create_shape n'a pas retourné d'instance valide." << std::endl;
            dlclose(handle);
            return nullptr;
        }
        auto positionedShape = std::make_unique<PositionedShape>(std::unique_ptr<IShape>(shape), position, 0.0);
        auto coloredPlane = std::make_unique<ColoredShape>(std::move(positionedShape), r, g, b);

        return coloredPlane;
    }

}