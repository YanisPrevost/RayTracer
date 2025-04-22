#include <iostream>
#include "Camera/Camera.hpp"
#include "Utils/ShapeLoader.hpp"
#include "Utils/utils.hpp"

int main() {
    const int width = 400;
    const int height = 400;

    RayTracer::Camera cam;

    RayTracer::ShapeLoader shapeLoader;

    if (!shapeLoader.loadShapeLibrary("./Plugins/Primitives/libsphere.so")) {
        std::cerr << "Impossible de charger la sphère." << std::endl;
        return 1;
    }

    const auto& shapes = shapeLoader.getShapes();
    if (shapes.empty()) {
        std::cerr << "Aucune forme n'a été chargée." << std::endl;
        return 1;
    }
    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for (int j = height - 1; j >= 0; --j) {
        for (int i = 0; i < width; ++i) {
            double u = static_cast<double>(i) / (width - 1);
            double v = static_cast<double>(j) / (height - 1);
            RayTracer::Ray r = cam.ray(u, v);
            bool hit = false;
            for (const auto& shape : shapes) {
                if (shape->hits(r)) {
                    hit = true;
                    break;
                }
            }

            if (hit) {
                RayTracer::write_color(Math::Vector3D(1, 0, 0)); // Rouge
            } else {
                RayTracer::write_color(Math::Vector3D(0, 0, 1)); // Bleu
            }
        }
    }

    std::cerr << "Image générée. Redirection vers un fichier .ppm pour visualisation.\n";
    return 0;
}