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

            // Cam_info _camInfo;
            ArgumentMap _cameraInfo;
            std::unordered_map<std::string, std::vector<ArgumentMap>> _primitivesInfo;
            std::unordered_map<std::string, std::vector<ArgumentMap>> _lightsInfo;
            // std::vector<Sphere_info> _sphereInfos;
            // std::vector<Cones_Info> _conesInfos;
            // std::vector<Plane_info> _planeInfos;
            // std::vector<Light_Point> _lightPointInfos;
            // std::vector<Light_Direction> _lightDirectionInfos;

        public:
            Parsing_cfg(const std::string& filename) : _filename(filename) {}
            ~Parsing_cfg() = default;
            ArgumentMap generateMap(libconfig::Setting &settings);
            void parse();
            void parseCamera(libconfig::Config& cfg);
            // void parseSpheres(libconfig::Config& cfg);
            // void parsePlanes(libconfig::Config& cfg);
            // void parseCones(libconfig::Config& cfg);
            // void parseLights(libconfig::Config& cfg);

            // Getters
            ArgumentMap& getCamInfo() { return _cameraInfo; }
            // const std::vector<Sphere_info>& getSphereInfos() const { return _sphereInfos; }
            // const std::vector<Cones_Info>& getConesInfos() const { return _conesInfos; }
            // const std::vector<Plane_info>& getPlaneInfos() const { return _planeInfos; }
            const std::unordered_map<std::string, std::vector<ArgumentMap>> &getPrimitiveInfo() const {return _primitivesInfo;}
            const std::unordered_map<std::string, std::vector<ArgumentMap>> &getLightsInfo() const {return _lightsInfo;}
            // const std::vector<Light_Point>& getLightPointInfos() const { return _lightPointInfos; }
            // const std::vector<Light_Direction>& getLightDirectionInfos() const { return _lightDirectionInfos; }
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
