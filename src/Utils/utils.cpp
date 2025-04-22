/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** utils.cpp
*/

#include "utils.hpp"

namespace RayTracer {
    void write_color(const Math::Vector3D& color)
    {
        int r = static_cast<int>(255.999 * color.getX());
        int g = static_cast<int>(255.999 * color.getY());
        int b = static_cast<int>(255.999 * color.getZ());

        std::cout << r << ' ' << g << ' ' << b << '\n';
    }
}
