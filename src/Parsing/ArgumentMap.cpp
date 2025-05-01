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
    // template <typename T>
    // T &ArgumentMap::Assigner::as() {
    //     return (std::any_cast<T&> (_val));
    // }

    // template<typename T>
    // ArgumentMap::Assigner &ArgumentMap::Assigner::operator=(T val)
    // {
    //     _val = val;
    //     return *this;
    // }
}