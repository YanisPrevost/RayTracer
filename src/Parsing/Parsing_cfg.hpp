/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.hpp
*/

#pragma once
#include <iostream>
#include <fstream>

namespace RayTracer
{
    class Parsing_cfg {
        private:
            const std::string _filename;
        public:
            Parsing_cfg(const std::string& filename) : _filename(filename) {}
            ~Parsing_cfg() = default;
            void parse();
    };
}
