/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.cpp
*/

#include "Parsing_cfg.hpp"
#include "ArgumentMap.hpp"
#include "../Vectors/Vector.hpp"
#include "../Points/Points.hpp"

namespace RayTracer {

    ArgumentMap Parsing_cfg::generateMap(libconfig::Setting &settings)
    {
        ArgumentMap map;
        for (auto &info : settings) {
            std::string name = info.getName();
            if (info.isGroup()) {
                if (name == "color" && info.exists("r") && info.exists("g") && info.exists("b")) {
                    int r, g, b;
                    info.lookupValue("r", r);
                    info.lookupValue("g", g);
                    info.lookupValue("b", b);
                    map[name] = Math::Vector3D(r / 255.0, g / 255.0, b / 255.0);
                    continue;
                }
                map[name] = generateMap(info);
                continue;
            }
            switch (info.getType()) {
                case libconfig::Setting::Type::TypeFloat:
                    map[name] = static_cast<double>(info);
                    break;
                case libconfig::Setting::Type::TypeString:
                    map[name] = static_cast<std::string>(info);
                    break;
                case libconfig::Setting::Type::TypeBoolean :
                    map[name] = static_cast<bool>(info);
                    break;
                case libconfig::Setting::Type::TypeInt :
                    map[name] = static_cast<int>(info);
                    break;
                default:
                    break;
            }
        }
        return map;
    }

    void Parsing_cfg::parseCamera(libconfig::Config& cfg)
    {
        if (!cfg.exists("camera")) {
            throw ParseError("Couldn't find camera");
        }
        libconfig::Setting &cameraSettings = cfg.lookup("camera");
        _cameraInfo = generateMap(cameraSettings);
    }

    void Parsing_cfg::parse() {

        libconfig::Config cfg;
        std::fstream file(_filename.c_str());
        if (!file.is_open()) {
            throw ParseError("Unable to open file");
        }
        file.close();
        cfg.readFile(_filename.c_str());

        parseCamera(cfg);

        if (cfg.exists("primitives")) {
            libconfig::Setting &primitives = cfg.lookup("primitives");
            for (auto &primitive : primitives) {
                std::string primitiveName = primitive.getName();
                for (auto &primitiveObject : primitive) {
                    (_primitivesInfo[primitiveName]).push_back(generateMap(primitiveObject));
                }
            }

        }
        if (cfg.exists("lights")) {
            libconfig::Setting &lights = cfg.lookup("lights");
            for (auto &light : lights) {
                std::string lightName = light.getName();
                for (auto &lightObject : light) {
                    (_lightsInfo[lightName]).push_back(generateMap(lightObject));
                }
            }
        }
    }
}