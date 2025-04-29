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
#include "Classes_infos.hpp"

namespace RayTracer
{
    class Parsing_cfg {
        private:
            const std::string _filename;
            Cam_info _camInfo;
            std::vector<Sphere_info> _sphereInfos;
            std::vector<Cones_Info> _conesInfos;
            std::vector<Plane_info> _planeInfos;

        public:
            Parsing_cfg(const std::string& filename) : _filename(filename) {}
            ~Parsing_cfg() = default;
            void parse();
            void parseCamera(libconfig::Config& cfg);
            void parseSpheres(libconfig::Config& cfg);
            void parsePlanes(libconfig::Config& cfg);
            void parseCones(libconfig::Config& cfg);


            // Getters for camera info
            const Cam_info& getCamInfo() const { return _camInfo; }

            // Getters for primitives info
            const std::vector<Sphere_info>& getSphereInfos() const { return _sphereInfos; }
            const std::vector<Cones_Info>& getConesInfos() const { return _conesInfos; }
            const std::vector<Plane_info>& getPlaneInfos() const { return _planeInfos; }
    };
}
