#include "PpmViewer.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

namespace RayTracer {

    PpmViewer::PpmViewer(const std::string& ppmFile, int width, int height)
        : windowWidth(width), windowHeight(height), raytracer(nullptr), lastRenderedLine(0), displayActive(false)
    {
        if (!ppmFile.empty()) {
            loadPpmFile(ppmFile);
        }
        displayImage.create(windowWidth, windowHeight, sf::Color::Black);
    }

    PpmViewer::~PpmViewer()
    {
        stopDisplay();
    }

    bool PpmViewer::loadPpmFile(const std::string& filePath)
    {
        ppmFilePath = filePath;
        return parsePpm();
    }

    bool PpmViewer::parsePpm()
    {
        std::ifstream file(ppmFilePath);
        if (!file.is_open()) {
            std::cerr << "Erreur: Impossible d'ouvrir le fichier PPM " << ppmFilePath << std::endl;
            return false;
        }
        std::string format;
        int width, height, maxVal;
        file >> format;
        char c;
        file.get(c);
        while (c == '\n' || c == ' ') {
            file.get(c);
            if (c == '#') {
                std::string comment;
                std::getline(file, comment);
                file.get(c);
            }
        }
        file.unget();
        file >> width >> height >> maxVal;
        if (format != "P3") {
            std::cerr << "Format PPM non supporté: " << format << std::endl;
            file.close();
            return false;
        }

        sf::Image image;
        image.create(width, height);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int r, g, b;
                file >> r >> g >> b;
                image.setPixel(x, y, sf::Color(r, g, b));
            }
        }

        file.close();
        texture.loadFromImage(image);
        sprite.setTexture(texture, true);
        if (windowWidth == 0 || windowHeight == 0) {
            windowWidth = width;
            windowHeight = height;
        }
        return true;
    }

    void PpmViewer::setWindowSize(int width, int height)
    {
        windowWidth = width;
        windowHeight = height;
    }

    void PpmViewer::start_rendering(RayTracer* raytracer)
    {
        if (displayActive.load() || !raytracer) {
            return;
        }

        this->raytracer = raytracer;
        lastRenderedLine = 0;
        displayActive.store(true);

        if (!window.isOpen()) {
            window.create(sf::VideoMode(windowWidth, windowHeight), "RayTracer");
        }

        displayImage.create(windowWidth, windowHeight, sf::Color::Black);
        texture.create(windowWidth, windowHeight);
        texture.update(displayImage);
        sprite.setTexture(texture, true);
        if (displayThread.joinable()) {
            displayThread.join();
        }
        displayThread = std::thread(&PpmViewer::displayLoop, this);
    }

    void PpmViewer::stopDisplay()
    {
        displayActive.store(false);
        if (displayThread.joinable()) {
            displayThread.join();
        }
        if (window.isOpen()) {
            window.close();
        }
        raytracer = nullptr;
    }

    void PpmViewer::updateTexture()
    {
        if (!raytracer || !displayActive.load()) {
            return;
        }

        const Screen& screen = raytracer->getScreen();
        int width = screen.getWidth();
        int height = screen.getHeight();
        int currentLine = raytracer->getCurrentLine();

        {
            std::lock_guard<std::mutex> lock(displayMutex);
            for (int y = lastRenderedLine; y < currentLine && y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    Math::Vector3D color = screen.getPixel(x, y);
                    // couleur de [0,1] à [0,255]
                    sf::Color pixelColor(
                        static_cast<sf::Uint8>(std::min(255.0, color.X * 255)),
                        static_cast<sf::Uint8>(std::min(255.0, color.Y * 255)),
                        static_cast<sf::Uint8>(std::min(255.0, color.Z * 255))
                    );
                    displayImage.setPixel(x, y, pixelColor);
                }
            }
            if (lastRenderedLine < currentLine) {
                texture.update(displayImage);
                lastRenderedLine = currentLine;
            }
        }
    }

    void PpmViewer::displayLoop()
    {
        float scaleX = static_cast<float>(windowWidth) / displayImage.getSize().x;
        float scaleY = static_cast<float>(windowHeight) / displayImage.getSize().y;
        sprite.setScale(scaleX, scaleY);

        displayActive.store(true);
        while (window.isOpen() && displayActive.load()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    displayActive.store(false);
                    return;
                }
            }

            updateTexture();
            window.clear(sf::Color::Black);
            window.draw(sprite);
            window.display();

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

}
