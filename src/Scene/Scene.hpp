/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Scene.hpp
*/

#pragma once

#include <vector>
#include <memory>
#include "../Camera/Camera.hpp"
#include "../Builders/ShapeBuilder.hpp"
#include "../Builders/Sphere/SphereBuilder.hpp"
#include "../Builders/Plane/PlaneBuilder.hpp"
#include "../Interfaces/IShape.hpp"
#include "../Parsing/Parsing_cfg.hpp"

namespace RayTracer {

    class Scene {
        private:
            std::unique_ptr<Camera> _camera;
            std::vector<std::unique_ptr<IShape>> _shapes;
            ShapeDirector _director;

        public:
            Scene();
            Scene(const Parsing_cfg& config);
            ~Scene() = default;

            void addSphere(const Math::Point3D& position, double radius, int r, int g, int b);
            void addPlane(const Math::Point3D& position, const std::string& axis, int r, int g, int b);

            void setCamera(const Cam_info& camInfo);

            void loadFromConfig(const Parsing_cfg& config);

            const Camera& getCamera() const;
            const std::vector<std::unique_ptr<IShape>>& getShapes() const;

            bool trace(const Ray& ray, Math::Vector3D& outColor) const;
    };

}
