/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** PpmViewer.hpp
*/

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

namespace RayTracer {

class PpmViewer {
    public:
        PpmViewer();
        ~PpmViewer();
        bool loadFromFile(const std::string& filename);
        bool loadFromPixelData(const std::vector<sf::Color>& pixels, int width, int height);
        void display();
        const sf::Image& getImage() const { return _image; }
    private:
        sf::RenderWindow _window;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::Image _image;
        int _width;
        int _height;
        bool _isLoaded;
    };

}
