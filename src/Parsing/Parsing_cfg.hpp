/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.hpp
*/

#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <libconfig.h++>
// #include "Classes_infos.hpp"
#include "ArgumentMap.hpp"

namespace RayTracer
{
    class Parsing_cfg {
        private:
            const std::string _filename;

            ArgumentMap _cameraInfo;
            std::unordered_map<std::string, std::vector<ArgumentMap>> _primitivesInfo;
            std::unordered_map<std::string, std::vector<ArgumentMap>> _lightsInfo;

        public:
            Parsing_cfg(const std::string& filename) : _filename(filename) {}
            ~Parsing_cfg() = default;
            ArgumentMap generateMap(libconfig::Setting &settings);
            void parse();
            void parseCamera(libconfig::Config& cfg);

            // Getters
            ArgumentMap& getCamInfo() { return _cameraInfo; }
            const std::unordered_map<std::string, std::vector<ArgumentMap>> &getPrimitiveInfo() const {return _primitivesInfo;}
            const std::unordered_map<std::string, std::vector<ArgumentMap>> &getLightsInfo() const {return _lightsInfo;}
            class ParseError : std::exception {
                public:
                ParseError(std::string errorMessage) : _errorMessage(errorMessage){}
                const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW {
                    return _errorMessage.c_str();
                }
                private:
                    std::string _errorMessage;
            };
    };
}
