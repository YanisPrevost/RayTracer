/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** utils.cpp
*/

#include "utils.hpp"

namespace RayTracer {

    std::mutex Utils::ppmFileMutex;
    std::ofstream Utils::ppmFile;
    bool Utils::ppmHeaderWritten = false;
    int Utils::imageWidth = 0;
    int Utils::imageHeight = 0;
    int Utils::completedPixels = 0;

    void Utils::init_ppm_file(int width, int height)
    {
        std::lock_guard<std::mutex> lock(ppmFileMutex);
        imageWidth = width;
        imageHeight = height;
        completedPixels = 0;
        ppmFile.open("output.ppm");
        if (ppmFile.is_open()) {
            ppmFile << "P3\n" << width << " " << height << "\n255\n";
            ppmHeaderWritten = true;
        }
    }

    void Utils::write_color(const Math::Vector3D& color)
    {
        int r = static_cast<int>(255.999 * color.getX());
        int g = static_cast<int>(255.999 * color.getY());
        int b = static_cast<int>(255.999 * color.getZ());

        std::lock_guard<std::mutex> lock(ppmFileMutex);
        if (ppmFile.is_open() && ppmHeaderWritten) {
            ppmFile << r << ' ' << g << ' ' << b << '\n';
            completedPixels++;
        }
    }

    void Utils::finalize_ppm_file()
    {
        std::lock_guard<std::mutex> lock(ppmFileMutex);
        if (ppmFile.is_open()) {
            ppmFile.close();
        }
    }
}
