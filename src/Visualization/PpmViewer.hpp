/*
** EPITECH PROJECT, 2024
** Zero
** File description:
** PpmViewer.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include "../Builder/RayTracer.hpp"
#include "../Camera/Camera.hpp"

namespace RayTracer {

    class PpmViewer {
        private:
            sf::RenderWindow window;
            sf::Texture texture;
            sf::Sprite sprite;
            sf::Image displayImage;
            std::string ppmFilePath;
            int windowWidth;
            int windowHeight;

            std::mutex displayMutex;
            RayCaster &_raycaster;
            int lastRenderedLine;
            std::atomic<bool> displayActive;
            std::thread displayThread;

        public:
            PpmViewer(const std::string& ppmFile, RayCaster &raytracer, int width, int height);
            ~PpmViewer();

            bool loadPpmFile(const std::string& filePath);
            bool parsePpm();

            void start_rendering();
            void stopDisplay();
            void displayLoop();
            void updateTexture();

            int getWindowWidth() const { return windowWidth; }
            int getWindowHeight() const { return windowHeight; }
            void setWindowSize(int width, int height);
            bool isDisplayActive() const { return displayActive.load(); }
        };

}
