/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** ArgumentMap
*/

#include "ArgumentMap.hpp"

namespace RayTracer {

    ArgumentMap::ArgumentMap()
    {
    }

    ArgumentMap::~ArgumentMap()
    {
    }

    ArgumentMap::Assigner ArgumentMap::operator[](std::string key)
    {
        return Assigner(_map[key]);
    }

}