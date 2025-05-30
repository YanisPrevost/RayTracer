/*
** EPITECH PROJECT, 2025
** raytracer
** File description:
** Scene
*/

#include "Scene.hpp"
#include "IPrimitive.hpp"
#include "ILights.hpp"

namespace RayTracer {

    Scene::~Scene()
    {
        _primitives.clear();
        _lights.clear();
    }

    void Scene::buildScene(Parsing_cfg &parsedData, LibraryManager &libraryHandles)
    {
        if (parsedData.getCamInfo()["backgroundColor"].exists<ArgumentMap>()) {
            ArgumentMap color = parsedData.getCamInfo()["backgroundColor"].as<ArgumentMap>();
            backgroundColor = Color(double(color["r"].as<int>() / 255.0), double(color["g"].as<int>() / 255.0), double(color["b"].as<int>() / 255.0));
        } else {
            backgroundColor = Color(0.2, 0.2, 0.2);
        }
        if (parsedData.getCamInfo()["ambientLight"].exists<ArgumentMap>()) {
            ArgumentMap color = parsedData.getCamInfo()["ambientLight"].as<ArgumentMap>();
            ambientLight = Color(color["r"].as<int>() / 255.0, color["g"].as<int>() / 255.0, color["b"].as<int>() / 255.0);
        } else {
            ambientLight = Color(0.1, 0.1, 0.1);
        }
        for (const auto &i : parsedData.getMaterialsInfo()) {
            materials[i.first] = Material(i.first, i.second);
        }
        const std::unordered_map<std::string, std::vector<ArgumentMap>> &primitivesInfo = parsedData.getPrimitiveInfo();
        std::vector<std::unique_ptr<IPrimitive>> primitives;
        for (const auto &primitive : primitivesInfo) {
            std::unique_ptr<DynamicLibrary> &currentPrimitive = libraryHandles.getCurrentLibrary(primitive.first, "getPrimitiveName");

            auto constructor = currentPrimitive->getConstructor<IPrimitive, ArgumentMap>("createPrimitive");

            for (auto params : primitive.second) {
                if (params["material"].exists<std::string>()) {
                    std::string materialName = params["material"].as<std::string>();
                    params["material"] = std::ref(this->materials[materialName]);
                }
                primitives.push_back(constructor(params));
            }
        }
        std::vector<std::unique_ptr<IPrimitive>> treePrimitives;
        for (auto &primitive : primitives) {
            if (primitive->getBoundingBox().isNull())
                _primitives.push_back(std::move(primitive));
            else
                treePrimitives.push_back(std::move(primitive));
        }
        tree = std::make_unique<Node>(std::move(treePrimitives));

        const std::unordered_map<std::string, std::vector<ArgumentMap>> &lightsInfo = parsedData.getLightsInfo();
            for (const auto &light : lightsInfo) {
                std::unique_ptr<DynamicLibrary> &currentLight = libraryHandles.getCurrentLightLibrary(light.first, "getLightName");
                auto constructor = currentLight->getConstructor<ILights, ArgumentMap>("createLight");
                for (auto params : light.second) {
                    addLight(constructor(params));
                }
            }
    }
}
