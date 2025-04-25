/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Scene.cpp
*/

#include "Scene.hpp"
#include <cstring>

namespace RayTracer {

    Scene::Scene() : _camera(nullptr) {}
    Scene::Scene(const Parsing_cfg& config) : _camera(nullptr)
    {
        loadFromConfig(config);
    }

    void Scene::addSphere(const Math::Point3D& position, double radius, int r, int g, int b)
    {
        SphereBuilder builder;

        builder.reset();
        builder.setPosition(position);
        builder.setRadius(radius);
        builder.setColor(r, g, b);
        _shapes.push_back(_director.createSphere(builder, position));
    }

    void Scene::addPlane(const Math::Point3D& position, const std::string& axis, int r, int g, int b)
    {
        PlaneBuilder builder;

        builder.reset();
        builder.setPosition(position);
        builder.setAxis(axis);
        builder.setColor(r, g, b);
        _shapes.push_back(_director.createPlane(builder, position));
    }

    void Scene::setCamera(const Cam_info& camInfo)
    {
        _camera = std::make_unique<Camera>(camInfo.getPosition(), camInfo.getFov(), camInfo.getWidth(), camInfo.getHeight());
    }

    void Scene::loadFromConfig(const Parsing_cfg& config)
    {
        setCamera(config.getCamInfo());

        for (const auto& planeInfo : config.getPlaneInfos()) {
            addPlane(planeInfo.getPosition(), planeInfo.getAxis(), planeInfo.getR(), planeInfo.getG(), planeInfo.getB());
        }
        for (const auto& sphereInfo : config.getSphereInfos()) {
            addSphere(sphereInfo.getPosition(), sphereInfo.getRadius(), sphereInfo.getR(), sphereInfo.getG(), sphereInfo.getB());
        }
    }

    const Camera& Scene::getCamera() const
    {
        return *_camera;
    }

    const std::vector<std::unique_ptr<IShape>>& Scene::getShapes() const
    {
        return _shapes;
    }

    bool Scene::trace(const Ray& ray, Math::Vector3D& outColor) const
    {
        bool hit = false;
        const IShape* hitShape = nullptr;

        for (auto it = _shapes.rbegin(); it != _shapes.rend(); ++it) {
            const auto& shape = *it;
            if (shape && shape->hits(ray)) {
                hit = true;
                hitShape = shape.get();
                break;
            }
        }
        if (hit) {
            if (hitShape && strcmp(hitShape->getType(), "ColoredShape") == 0) {
                const ColoredShape* coloredShape = dynamic_cast<const ColoredShape*>(hitShape);
                if (coloredShape) {
                    outColor = Math::Vector3D(
                        coloredShape->getRed() / 255.0,
                        coloredShape->getGreen() / 255.0,
                        coloredShape->getBlue() / 255.0
                    );
                }
            }
        } else {
            outColor = Math::Vector3D(0.0, 0.0, 0.0);
        }
        return hit;
    }

}
