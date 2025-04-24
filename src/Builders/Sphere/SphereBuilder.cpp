/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** ShapeBuilder.cpp
*/

#include "SphereBuilder.hpp"
#include "../../Interfaces/IShape.hpp"
#include "../../Primitives/ShapeDecorator.hpp"
#include "../../Primitives/PositionedShape.hpp"
#include <memory>
#include <dlfcn.h>
#include <iostream>

namespace RayTracer {

    std::unique_ptr<IShape> SphereBuilder::build() {
        void* handle = dlopen("./Plugins/Primitives/libsphere.so", RTLD_LAZY);
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
        auto positionedShape = std::make_unique<PositionedShape>(std::unique_ptr<IShape>(shape), center, radius);
        auto coloredSphere = std::make_unique<ColoredShape>(std::move(positionedShape), r, g, b);

        return coloredSphere;
    }

}
