/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** Screen.hpp
*/

#pragma once

#include "Vector.hpp"
#include "Points.hpp"
#include <vector>
#include <string>
#include "../Parsing/ArgumentMap.hpp"

namespace RayTracer {

    class Screen {
        private:
            int width;
            int height;
            std::vector<Math::Vector3D> pixels;
            std::vector<bool> completedLines;
        public:
            Screen(int width = 800, int height = 600);
            Screen(ArgumentMap params);
            int getWidth() const { return width; }
            int getHeight() const { return height; }
            Math::Vector3D getPixel(int x, int y) const;
            void setPixel(int x, int y, const Math::Vector3D& color);
            void setPixel(int n, const Math::Vector3D& color);
            void getUV(int x, int y, double& u, double& v) const;
            bool saveToPPM(const std::string& filename) const;
            const std::vector<bool> &getCompletedLines() const {return completedLines;}
            void setLineCompleted(int y) {completedLines[y] = true;}
    };
}