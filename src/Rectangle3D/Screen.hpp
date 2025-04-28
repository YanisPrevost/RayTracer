/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Screen.hpp
*/

#pragma once

#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"
#include <vector>
#include <string>

namespace RayTracer {

    class Screen {
        private:
            int width;
            int height;
            std::vector<Math::Vector3D> pixels;
        public:
            Screen(int width = 800, int height = 600);

            int getWidth() const { return width; }
            int getHeight() const { return height; }
            Math::Vector3D getPixel(int x, int y) const;
            void setPixel(int x, int y, const Math::Vector3D& color);
            void getUV(int x, int y, double& u, double& v) const;
            bool saveToPPM(const std::string& filename) const;
        };

}
