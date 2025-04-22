/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PpmViewer.cpp
*/

#include "PpmViewer.hpp"
#include <sstream>

namespace RayTracer {

    PpmViewer::PpmViewer() : _width(0), _height(0), _isLoaded(false) {}

    PpmViewer::~PpmViewer()
    {
        if (_window.isOpen()) {
            _window.close();
        }
    }

    bool PpmViewer::loadFromFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier PPM: " << filename << std::endl;
            return false;
        }
        std::string format;
        file >> format;
        if (format != "P3") {
            std::cerr << "Format PPM non supporté: " << format << std::endl;
            return false;
        }
        file >> _width >> _height;
        int maxValue;
        file >> maxValue;

        _image.create(_width, _height);

        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                int r, g, b;
                file >> r >> g >> b;
                if (maxValue != 255) {
                    r = static_cast<int>(r * 255.0 / maxValue);
                    g = static_cast<int>(g * 255.0 / maxValue);
                    b = static_cast<int>(b * 255.0 / maxValue);
                }
                _image.setPixel(x, _height - 1 - y, sf::Color(r, g, b));
            }
        }
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
        _isLoaded = true;
        return true;
    }

    bool PpmViewer::loadFromPixelData(const std::vector<sf::Color>& pixels, int width, int height)
    {
        if (pixels.size() != static_cast<size_t>(width * height)) {
            std::cerr << "Taille des données de pixels incorrecte" << std::endl;
            return false;
        }
        _width = width;
        _height = height;
        _image.create(_width, _height);
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                _image.setPixel(x, y, pixels[y * _width + x]);
            }
        }
        _texture.loadFromImage(_image);
        _sprite.setTexture(_texture);
        _isLoaded = true;
        return true;
    }

    void PpmViewer::display()
    {
        if (!_isLoaded) {
            std::cerr << "Aucune image n'a été chargée" << std::endl;
            return;
        }
        _window.create(sf::VideoMode(_width, _height), "RayTracer - Visualisation");
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                }
            }

            _window.clear();
            _window.draw(_sprite);
            _window.display();
        }
    }

}
