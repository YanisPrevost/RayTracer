/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.cpp
*/

#include "Parsing_cfg.hpp"

namespace RayTracer
{
    void Parsing_cfg::parse() {
        std::ifstream file(_filename);
        if (!file.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier de configuration: " << _filename << std::endl;
            return;
        }
        file.close();
    }
}