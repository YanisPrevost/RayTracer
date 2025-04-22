/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** utils.hpp
*/

#pragma once

#include "../Vectors/Vector3D.hpp"
#include <iostream>
#include <fstream>
#include <mutex>

namespace RayTracer {
    class Utils {
        private:
            static std::ofstream ppmFile;
        public:
            static std::mutex ppmFileMutex;
            static bool ppmHeaderWritten;
            static int imageWidth;
            static int imageHeight;
            static int completedPixels;
            static void init_ppm_file(int width, int height);
            static void write_color(const Math::Vector3D& color);
            static void finalize_ppm_file();
    };
}
