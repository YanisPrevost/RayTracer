/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Parsing_cfg.cpp
*/

#include "Parsing_cfg.hpp"

namespace RayTracer
{

    void Parsing_cfg::parseCamera(libconfig::Config& cfg)
    {
        int x, y, z;
        if (cfg.exists("camera")) {
            if (!(cfg.lookupValue("camera.fieldOfView", _camInfo._fov) &&
            cfg.lookupValue("camera.resolution.width", _camInfo._width) &&
            cfg.lookupValue("camera.resolution.height", _camInfo._height))) {
                std::cerr << "Error: Missing camera parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }
            if (cfg.lookupValue("camera.position.x", x) && cfg.lookupValue("camera.position.y", y) && cfg.lookupValue("camera.position.z", z))
                _camInfo._position = Math::Point3D(x, y, z);

            if (cfg.lookupValue("camera.rotation.x", x) && cfg.lookupValue("camera.rotation.y", y) && cfg.lookupValue("camera.rotation.z", z))
                _camInfo._rotation = Math::Point3D(x, y, z);
            else
                _camInfo._rotation = Math::Point3D(0, 0, 0);
                // EXCEPTION A FAIRE ICI
        }
    }

    void Parsing_cfg::parsePlanes(libconfig::Config& cfg)
    {
        libconfig::Setting& planes = cfg.lookup("primitives.planes");
        int numPlanes = planes.getLength();
        for (int i = 0; i < numPlanes; ++i) {
            libconfig::Setting& plane = planes[i];
            Plane_info planeInfo;
            std::string axis;
            int position;
            int r, g, b;

            if (!(plane.lookupValue("axis", axis) &&
            plane.lookupValue("position", position))) {
                std::cerr << "Error: Missing axis or position parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }

            const libconfig::Setting& color = plane["color"];

            if (!(color.lookupValue("r", r) &&
            color.lookupValue("g", g) &&
            color.lookupValue("b", b))) {
                std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }

            if (axis == "X") {
                planeInfo.setPosition(Math::Point3D(position, 0, 0));
            } else if (axis == "Y") {
                planeInfo.setPosition(Math::Point3D(0, position, 0));
            } else if (axis == "Z") {
                planeInfo.setPosition(Math::Point3D(0, 0, position));
            } else {
                // EXCEPTION A FAIRE ICI
            }
            planeInfo.setColor(r, g, b);
            _planeInfos.push_back(planeInfo);
        }
    }

    void Parsing_cfg::parseCones(libconfig::Config& cfg)
    {
        libconfig::Setting& cones = cfg.lookup("primitives.cones");
        int numCones = cones.getLength();
        for (int i = 0; i < numCones; ++i) {
            libconfig::Setting& cone = cones[i];
            Cones_Info conesInfo;
            int x, y, z;
            int radius;
            int _height;
            int r, g, b;
            int d_x, d_y, d_z;

            const libconfig::Setting& position = cone["position"];
            if (!(position.lookupValue("x", x) && position.lookupValue("y", y) && position.lookupValue("z", z))) {
                std::cerr << "Error: Missing position parameters (x, y, z) in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }
            const libconfig::Setting& direction = cone["direction"];
            if (!(direction.lookupValue("d_x", d_x) && direction.lookupValue("d_y", d_y) && direction.lookupValue("d_z", d_z))) {
                std::cerr << "Error: Missing direction parameters (x, y, z) in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }
            if (!(cone.lookupValue("radius", radius) && cone.lookupValue("height", _height))) {
                std::cerr << "Error: Missing radius or height parameter in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE I
            }
            const libconfig::Setting& color = cone["color"];

            if (!(color.lookupValue("r", r) &&
            color.lookupValue("g", g) &&
            color.lookupValue("b", b))) {
                std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }

            conesInfo.setHeight(_height);
            conesInfo.setRadius(radius);
            conesInfo.setPosition(Math::Point3D(x, y, z));
            conesInfo.setDirection(Math::Point3D(d_x, d_y, d_z));
            conesInfo.setColor(r, g, b);
            _conesInfos.push_back(conesInfo);
        }
    }

    void Parsing_cfg::parseSpheres(libconfig::Config& cfg)
    {
        libconfig::Setting& spheres = cfg.lookup("primitives.spheres");
        int numSpheres = spheres.getLength();
        for (int i = 0; i < numSpheres; ++i) {
            libconfig::Setting& sphere = spheres[i];
            Sphere_info sphereInfo;
            int x, y, z;
            int radius = 0;
            int r, g, b;

            if (!(sphere.lookupValue("x", x) &&
            sphere.lookupValue("y", y) &&
            sphere.lookupValue("z", z) &&
            sphere.lookupValue("r", radius)))
            {
                std::cerr << "Error: Missing x, y, z or radius parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }

            const libconfig::Setting& color = sphere["color"];

            if (!(color.lookupValue("r", r) &&
            color.lookupValue("g", g) &&
            color.lookupValue("b", b))) {
                std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            }
            sphereInfo.setPosition(Math::Point3D(x, y, z));
            sphereInfo.setRadius(radius);
            sphereInfo.setColor(r, g, b);
            _sphereInfos.push_back(sphereInfo);
        }
    }

    void Parsing_cfg::parseLights(libconfig::Config& cfg)
    {
        libconfig::Setting& lights = cfg.lookup("primitives.lights");
        int numLights = lights.getLength();
        for (int i = 0; i < numLights; ++i) {
            libconfig::Setting& _lights = lights[i];
            Light_Info lightInfo;
            Light_Direction lightDirection;
            Light_Point lightPoint;

            double ambient, diffuse, intensity;
            int x, y, z;
            int r, g, b;
            if (!(_lights.lookupValue("ambient", ambient) &&
            _lights.lookupValue("diffuse", diffuse))) {
                std::cerr << "Error: Missing ambient or diffuse parameters in the configuration file." << std::endl;
                exit(84);
                // EXCEPTION A FAIRE ICI
            } else {
                lightInfo.setAmbient(ambient);
                lightInfo.setDiffuse(diffuse);
            }

            if (_lights.exists("point")) {
                libconfig::Setting& point = _lights.lookup("point");

                const libconfig::Setting& position = point["position"];

                if (!(position.lookupValue("x", x) &&
                position.lookupValue("y", y) &&
                position.lookupValue("z", z))) {
                    std::cerr << "Error: Missing position parameters in the configuration file." << std::endl;
                    exit(84);
                    // EXCEPTION A FAIRE ICI
                }

                const libconfig::Setting& color = point["color"];
                if (!(color.lookupValue("r", r) &&
                color.lookupValue("g", g) &&
                color.lookupValue("b", b))) {
                    std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
                    exit(84);
                    // EXCEPTION A FAIRE ICI
                }
                lightPoint.setPosition(Math::Point3D(x, y, z));
                lightPoint.setColor(r, g, b);
            } else if (_lights.exists("directional")) {
                libconfig::Setting& directional = _lights.lookup("directional");

                directional.lookupValue("intensity", intensity);

                const libconfig::Setting& direction = directional["direction"];

                if (!(direction.lookupValue("x", x) &&
                direction.lookupValue("y", y) &&
                direction.lookupValue("z", z))) {
                    std::cerr << "Error: Missing direction parameters in the configuration file." << std::endl;
                    exit(84);
                    // EXCEPTION A FAIRE ICI
                }

                const libconfig::Setting& color = directional["color"];
                if (!(color.lookupValue("r", r) &&
                color.lookupValue("g", g) &&
                color.lookupValue("b", b))) {
                    std::cerr << "Error: Missing color parameters in the configuration file." << std::endl;
                    exit(84);
                    // EXCEPTION A FAIRE ICI
                }
                lightDirection.setDirection(Math::Point3D(x, y, z));
                lightDirection.setColor(r, g, b);
                lightDirection.setIntensity(intensity);
            }
        }
    }

    void Parsing_cfg::parse() {

        libconfig::Config cfg;
        std::fstream file(_filename.c_str());
        if (!file.is_open()) {
            std::cerr << "Error: Unable to open file " << _filename << std::endl;
            exit(84);
        }
        file.close();
        cfg.readFile(_filename.c_str());

        parseCamera(cfg);

        if (cfg.exists("primitives")) {
            parseSpheres(cfg);
            parsePlanes(cfg);
            parseCones(cfg);
        }
        if (cfg.exists("lights")) {
            // parseLights(cfg);
        }
    }
}