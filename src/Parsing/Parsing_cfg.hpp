/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.hpp
*/

#pragma once
#include <iostream>
#include <fstream>
#include "Points/Point3D.hpp"
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
            std::vector<Plane_info> _planeInfos;

        public:
            Parsing_cfg(const std::string& filename) : _filename(filename) {}
            ~Parsing_cfg() = default;
            void parse();

            // Getters for camera info
            const Cam_info& getCamInfo() const { return _camInfo; }

            // Getters for primitives info
            const std::vector<Sphere_info>& getSphereInfos() const { return _sphereInfos; }
            const std::vector<Plane_info>& getPlaneInfos() const { return _planeInfos; }
    };
}
