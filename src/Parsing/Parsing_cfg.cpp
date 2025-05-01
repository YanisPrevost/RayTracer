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
namespace RayTracer
{

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
                    map[name] = Math::Vector3D(r, g, b);
                    continue;
                }
                map[name] = generateMap(info);
                continue;
            }
            switch (info.getType())
            {
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
        // int x, y, z;
        if (!cfg.exists("camera")) {
            throw ParseError("Couldn't find camera");
        }
        libconfig::Setting &cameraSettings = cfg.lookup("camera");
        _cameraInfo = generateMap(cameraSettings);
        // if (!(cfg.lookupValue("camera.fieldOfView", _camInfo._fov) &&
        // cfg.lookupValue("camera.resolution.width", _camInfo._width) &&
        // cfg.lookupValue("camera.resolution.height", _camInfo._height))) {
        //     std::cerr << "Error: Missing camera parameters in the configuration file." << std::endl;
        //     exit(84);
        //     // EXCEPTION A FAIRE ICI
        // }
        // if (cfg.lookupValue("camera.position.x", x) && cfg.lookupValue("camera.position.y", y) && cfg.lookupValue("camera.position.z", z)) 
        //     cameraMap["position"] = Math::Point3D(x, y, z);
        //     // _camInfo._position = Math::Point3D(x, y, z);

        // if (cfg.lookupValue("camera.rotation.x", x) && cfg.lookupValue("camera.rotation.y", y) && cfg.lookupValue("camera.rotation.z", z)) {
        //     cameraMap["rotation"] = Math::Point3D(x, y, z);
        //     // _camInfo._rotation = Math::Point3D(x, y, z);
        // } else {
        //     cameraMap["rotation"] = Math::Point3D(0, 0, 0);
        //     _camInfo._rotation = Math::Point3D(0, 0, 0);
        // }
            // EXCEPTION A FAIRE ICI
    }

    // void Parsing_cfg::parsePlanes(libconfig::Config& cfg)
    // {
    //     libconfig::Setting& planes = cfg.lookup("primitives.planes");
    //     int numPlanes = planes.getLength();
    //     for (int i = 0; i < numPlanes; ++i) {
    //         libconfig::Setting& plane = planes[i];
    //         Plane_info planeInfo;
    //         std::string axis;
    //         int position;
    //         int r, g, b;

    //         if (!(plane.lookupValue("axis", axis) &&
    //         plane.lookupValue("position", position))) {
    //             std::cerr << "Error: Missing axis or position parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         }

    //         const libconfig::Setting& color = plane["color"];

    //         if (!(color.lookupValue("r", r) &&
    //         color.lookupValue("g", g) &&
    //         color.lookupValue("b", b))) {
    //             std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         }

    //         if (axis == "X") {
    //             planeInfo.setPosition(Math::Point3D(position, 0, 0));
    //         } else if (axis == "Y") {
    //             planeInfo.setPosition(Math::Point3D(0, position, 0));
    //         } else if (axis == "Z") {
    //             planeInfo.setPosition(Math::Point3D(0, 0, position));
    //         } else {
    //             // EXCEPTION A FAIRE ICI
    //         }
    //         planeInfo.setColor(r, g, b);
    //         _planeInfos.push_back(planeInfo);
    //     }
    // }

    // void Parsing_cfg::parseCones(libconfig::Config& cfg)
    // {
    //     libconfig::Setting& cones = cfg.lookup("primitives.cones");
    //     int numCones = cones.getLength();
    //     for (int i = 0; i < numCones; ++i) {
    //         libconfig::Setting& cones = cones[i];
    //         Cones_Info conesInfo;
    //         std::string axis;
    //         int position;
    //         double radius;
    //         int _height;
    //         int r, g, b;

    //         if (!(cones.lookupValue("axis", axis) &&
    //         cones.lookupValue("position", position) &&
    //         cones.lookupValue("heigth", _height) &&
    //         cones.lookupValue("r", radius))) {
    //             std::cerr << "Error: Missing axis or position parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         }

    //         const libconfig::Setting& color = cones["color"];

    //         if (!(color.lookupValue("r", r) &&
    //         color.lookupValue("g", g) &&
    //         color.lookupValue("b", b))) {
    //             std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         }

    //         if (axis == "X") {
    //             conesInfo.setPosition(Math::Point3D(position, 0, 0));
    //         } else if (axis == "Y") {
    //             conesInfo.setPosition(Math::Point3D(0, position, 0));
    //         } else if (axis == "Z") {
    //             conesInfo.setPosition(Math::Point3D(0, 0, position));
    //         } else {
    //             // EXCEPTION A FAIRE ICI
    //         }
    //         conesInfo.setAxis(axis);
    //         conesInfo.setHeight(_height);
    //         conesInfo.setRadius(radius);
    //         conesInfo.setColor(r, g, b);
    //         _conesInfos.push_back(conesInfo);
    //     }
    // }

    // void Parsing_cfg::parseSpheres(libconfig::Config& cfg)
    // {
    //     libconfig::Setting& spheres = cfg.lookup("primitives.spheres");
    //     int numSpheres = spheres.getLength();
    //     for (int i = 0; i < numSpheres; ++i) {
    //         libconfig::Setting& sphere = spheres[i];
    //         Sphere_info sphereInfo;
    //         int x, y, z;
    //         int radius = 0;
    //         int r, g, b;

    //         if (!(sphere.lookupValue("x", x) &&
    //         sphere.lookupValue("y", y) &&
    //         sphere.lookupValue("z", z) &&
    //         sphere.lookupValue("r", radius)))
    //         {
    //             std::cerr << "Error: Missing x, y, z or radius parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         }

    //         const libconfig::Setting& color = sphere["color"];

    //         if (!(color.lookupValue("r", r) &&
    //         color.lookupValue("g", g) &&
    //         color.lookupValue("b", b))) {
    //             std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         }
    //         sphereInfo.setPosition(Math::Point3D(x, y, z));
    //         sphereInfo.setRadius(radius);
    //         sphereInfo.setColor(r, g, b);
    //         _sphereInfos.push_back(sphereInfo);
    //     }
    // }

    // void Parsing_cfg::parseLights(libconfig::Config& cfg)
    // {
    //     libconfig::Setting& lights = cfg.lookup("primitives.lights");
    //     int numLights = lights.getLength();
    //     for (int i = 0; i < numLights; ++i) {
    //         libconfig::Setting& _lights = lights[i];
    //         Light_Info lightInfo;
    //         Light_Direction lightDirection;
    //         Light_Point lightPoint;

    //         double ambient, diffuse, intensity;
    //         int x, y, z;
    //         int r, g, b;
    //         if (!(_lights.lookupValue("ambient", ambient) &&
    //         _lights.lookupValue("diffuse", diffuse))) {
    //             std::cerr << "Error: Missing ambient or diffuse parameters in the configuration file." << std::endl;
    //             exit(84);
    //             // EXCEPTION A FAIRE ICI
    //         } else {
    //             lightInfo.setAmbient(ambient);
    //             lightInfo.setDiffuse(diffuse);
    //         }

    //         if (_lights.exists("point")) {
    //             libconfig::Setting& point = _lights.lookup("point");

    //             const libconfig::Setting& position = point["position"];

    //             if (!(position.lookupValue("x", x) &&
    //             position.lookupValue("y", y) &&
    //             position.lookupValue("z", z))) {
    //                 std::cerr << "Error: Missing position parameters in the configuration file." << std::endl;
    //                 exit(84);
    //                 // EXCEPTION A FAIRE ICI
    //             }

    //             const libconfig::Setting& color = point["color"];
    //             if (!(color.lookupValue("r", r) &&
    //             color.lookupValue("g", g) &&
    //             color.lookupValue("b", b))) {
    //                 std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
    //                 exit(84);
    //                 // EXCEPTION A FAIRE ICI
    //             }
    //             lightPoint.setPosition(Math::Point3D(x, y, z));
    //             lightPoint.setColor(r, g, b);
    //         } else if (_lights.exists("directional")) {
    //             libconfig::Setting& directional = _lights.lookup("directional");

    //             directional.lookupValue("intensity", intensity);

    //             const libconfig::Setting& direction = directional["direction"];

    //             if (!(direction.lookupValue("x", x) &&
    //             direction.lookupValue("y", y) &&
    //             direction.lookupValue("z", z))) {
    //                 std::cerr << "Error: Missing direction parameters in the configuration file." << std::endl;
    //                 exit(84);
    //                 // EXCEPTION A FAIRE ICI
    //             }

    //             const libconfig::Setting& color = directional["color"];
    //             if (!(color.lookupValue("r", r) &&
    //             color.lookupValue("g", g) &&
    //             color.lookupValue("b", b))) {
    //                 std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
    //                 exit(84);
    //                 // EXCEPTION A FAIRE ICI
    //             }
    //             lightDirection.setDirection(Math::Point3D(x, y, z));
    //             lightDirection.setColor(r, g, b);
    //             lightDirection.setIntensity(intensity);
    //         }
    //     }
    // }

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
            // parseSpheres(cfg);
            // parsePlanes(cfg);
            // parseCones(cfg);
        }
        if (cfg.exists("lights")) {
            libconfig::Setting &lights = cfg.lookup("lights");
            for (auto &light : lights) {
                std::string lightName = light.getName();
                for (auto &lightObject : light) {
                    (_lightsInfo[lightName]).push_back(generateMap(lightObject));
                }
            }
            // parseLights(cfg);
        }
    }
}