/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Screen.cpp
*/

#include "Screen.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

namespace RayTracer {

    Screen::Screen(int width, int height) : width(width), height(height)
    {
        pixels.resize(width * height, Math::Vector3D(0, 0, 0));
    }

    Screen::Screen(ArgumentMap params) : width(params["width"].as<int>()), height(params["height"].as<int>())
    {
        pixels.resize(width * height, Math::Vector3D(0, 0, 0));
    }

    Math::Vector3D Screen::getPixel(int x, int y) const
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return Math::Vector3D(0, 0, 0);
        return pixels[y * width + x];
    }

    void Screen::setPixel(int x, int y, const Math::Vector3D& color)
    {
        if (x < 0 || x >= width || y < 0 || y >= height)
            return;
        double r = std::max(0.0, std::min(1.0, color.X));
        double g = std::max(0.0, std::min(1.0, color.Y));
        double b = std::max(0.0, std::min(1.0, color.Z));
        pixels[y * width + x] = Math::Vector3D(r, g, b);
    }

    void Screen::setPixel(int n, const Math::Vector3D& color)
    {
        if (n < 0 || n >= height * width)
            return;
        double r = std::max(0.0, std::min(1.0, color.X));
        double g = std::max(0.0, std::min(1.0, color.Y));
        double b = std::max(0.0, std::min(1.0, color.Z));
        pixels[n] = Math::Vector3D(r, g, b);
    }

    void Screen::getUV(int x, int y, double& u, double& v) const
    {
        u = static_cast<double>(x) / (width - 1);
        v = 1.0 - static_cast<double>(y) / (height - 1);
    }

    bool Screen::saveToPPM(const std::string& filename) const
    {
        std::ofstream file(filename, std::ios::out | std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Erreur: Impossible d'ouvrir le fichier " << filename << std::endl;
            return false;
        }
        file << "P3\n" << width << " " << height << "\n255\n";
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                Math::Vector3D color = getPixel(x, y);
                int r = static_cast<int>(color.X * 255.999);
                int g = static_cast<int>(color.Y * 255.999);
                int b = static_cast<int>(color.Z * 255.999);
                file << r << " " << g << " " << b << "\n";
            }
        }
        file.close();
        return true;
    }

}
