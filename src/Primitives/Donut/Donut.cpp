/*
** EPITECH PROJECT, 2024
** RayTracer
** File description:
** Donut.cpp
*/

#include "Donut.hpp"
#include <cmath>
#include <algorithm>
#include <vector>
#include "../../Parsing/ArgumentMap.hpp"

namespace RayTracer {

    Donut::Donut(const Math::Point3D& center, double majorRadius, double minorRadius, const Math::Vector3D& color, double reflection, const Math::Vector3D& direction)
        : center(center), majorRadius(majorRadius), minorRadius(minorRadius), color(color), reflection(reflection), direction(direction.normalize()) {}

    Donut::Donut(const std::vector<double>& params) :
        center(params[0], params[1], params[2]),
        majorRadius(params[3]),
        minorRadius(params[4]),
        color(params[5], params[6], params[7]),
        reflection(params[8]),
        direction(params[9], params[10], params[11])
    {
        direction = direction.normalize();
    }


    Donut::Donut(ArgumentMap params)
    {
        center = params["position"].as<Math::Point3D>();
        majorRadius = params["major_radius"].as<double>();
        minorRadius = params["minor_radius"].as<double>();
        color = params["color"].as<Math::Vector3D>();
        ArgumentMap directionMap = params["direction"].as<ArgumentMap>();
        direction = Math::Vector3D(directionMap["x"].as<double>(), directionMap["y"].as<double>(), directionMap["z"].as<double>());
        reflection = 0.0;
    }

    HitInfo Donut::intersect(const Ray& ray) const
    {
        HitInfo info;
        info.hit = false;

        Ray localRay = ray;
        Math::Point3D newOrigin(
            localRay.origin.X - center.X,
            localRay.origin.Y - center.Y,
            localRay.origin.Z - center.Z
        );
        localRay.origin = newOrigin;
        Math::Vector3D up = direction;
        Math::Vector3D right, forward;
        if (std::abs(up.X) < 0.9)
            right = Math::Vector3D(1, 0, 0).cross(up).normalize();
        else
            right = Math::Vector3D(0, 1, 0).cross(up).normalize();
        forward = up.cross(right).normalize();
        Math::Vector3D transformedOrigin(
            localRay.origin.X * right.X + localRay.origin.Y * right.Y + localRay.origin.Z * right.Z,
            localRay.origin.X * up.X + localRay.origin.Y * up.Y + localRay.origin.Z * up.Z,
            localRay.origin.X * forward.X + localRay.origin.Y * forward.Y + localRay.origin.Z * forward.Z
        );
        Math::Vector3D transformedDirection(
            localRay.direction.X * right.X + localRay.direction.Y * right.Y + localRay.direction.Z * right.Z,
            localRay.direction.X * up.X + localRay.direction.Y * up.Y + localRay.direction.Z * up.Z,
            localRay.direction.X * forward.X + localRay.direction.Y * forward.Y + localRay.direction.Z * forward.Z
        );
        localRay.origin = Math::Point3D(transformedOrigin.X, transformedOrigin.Y, transformedOrigin.Z);
        localRay.direction = transformedDirection.normalize();

        double R = majorRadius;
        double r = minorRadius;
        double R2 = R * R;
        double r2 = r * r;

        Math::Vector3D d = localRay.direction;
        Math::Vector3D o(localRay.origin.X, localRay.origin.Y, localRay.origin.Z);

        double a = d.dot(d);
        double b = 2.0 * o.dot(d);
        double c = o.dot(o) - R2 - r2;
        double a4 = a * a;
        double a3 = 2.0 * a * b;
        double a2 = b * b + 2.0 * a * c + 4.0 * R2 * d.Y * d.Y;
        double a1 = 2.0 * b * c + 8.0 * R2 * o.Y * d.Y;
        double a0 = c * c + 4.0 * R2 * (o.Y * o.Y - r2);

        a3 /= a4;
        a2 /= a4;
        a1 /= a4;
        a0 /= a4;
        a4 = 1.0;

        std::vector<double> roots;
        const double epsilon = 1e-6;
        const int maxIterations = 100;

        std::vector<double> initialGuesses = {-10.0, -1.0, 0.0, 1.0, 10.0};
        for (double guess : initialGuesses) {
            double t = guess;
            bool converged = false;
            for (int i = 0; i < maxIterations; ++i) {
                double P = a4*t*t*t*t + a3*t*t*t + a2*t*t + a1*t + a0;
                double Pprime = 4.0*a4*t*t*t + 3.0*a3*t*t + 2.0*a2*t + a1;
                if (std::abs(Pprime) < epsilon)
                    break;
                double t_new = t - P / Pprime;
                if (std::abs(t_new - t) < epsilon) {
                    converged = true;
                    t = t_new;
                    break;
                }
                t = t_new;
            }
            if (converged && t > epsilon) {
                bool isNew = true;
                for (double root : roots) {
                    if (std::abs(root - t) < epsilon) {
                        isNew = false;
                        break;
                    }
                }
                if (isNew)
                    roots.push_back(t);
            }
        }
        if (roots.empty())
            return info;
        std::sort(roots.begin(), roots.end());
        const double shadowEpsilon = 1e-3;
        double t = -1;
        for (double root : roots) {
            if (root > shadowEpsilon) {
                t = root;
                break;
            }
        }
        if (t < 0)
            return info;
        Math::Point3D hitPoint = localRay.origin + localRay.direction * t;
        double x = hitPoint.X;
        double y = hitPoint.Y;
        double z = hitPoint.Z;

        double dist = std::sqrt(x*x + z*z);
        double diff = std::sqrt((dist - R)*(dist - R) + y*y) - r;

        if (std::abs(diff) > 5e-3)
            return info;
        info.hit = true;
        info.distance = t;
        info.point = ray.origin + ray.direction * t;
        Math::Point3D localHitPoint = hitPoint;
        double distToRing = std::sqrt(localHitPoint.X*localHitPoint.X + localHitPoint.Z*localHitPoint.Z);
        Math::Vector3D ringToHit;
        if (distToRing > 1e-6) {
            double ringX = localHitPoint.X * R / distToRing;
            double ringZ = localHitPoint.Z * R / distToRing;
            ringToHit = Math::Vector3D(
                localHitPoint.X - ringX,
                localHitPoint.Y,
                localHitPoint.Z - ringZ
            );
            double distanceToOrigin = std::sqrt(localHitPoint.X*localHitPoint.X + localHitPoint.Z*localHitPoint.Z);
            bool isInside = distanceToOrigin < R;
            double dotProduct = ringToHit.dot(localRay.direction);
            if (dotProduct > 0) {
                ringToHit = ringToHit * (-1.0);
            }
        } else {
            ringToHit = Math::Vector3D(0, localHitPoint.Y > 0 ? 1 : -1, 0);
            if (localRay.direction.Y * ringToHit.Y > 0) {
                ringToHit.Y = -ringToHit.Y;
            }
        }
        Math::Vector3D normalizedRingToHit = ringToHit.normalize();
        Math::Vector3D globalNormal(
            normalizedRingToHit.X * right.X + normalizedRingToHit.Y * up.X + normalizedRingToHit.Z * forward.X,
            normalizedRingToHit.X * right.Y + normalizedRingToHit.Y * up.Y + normalizedRingToHit.Z * forward.Y,
            normalizedRingToHit.X * right.Z + normalizedRingToHit.Y * up.Z + normalizedRingToHit.Z * forward.Z
        );
        info.normal = globalNormal.normalize();
        info.color = color;
        info.reflection = reflection;
        return info;
    }

    std::string Donut::getName() const
    {
        return "Donut";
    }

    std::unique_ptr<IPrimitive> Donut::create(const std::vector<double>& params)
    {
        if (params.size() >= 8) {
            Math::Point3D center(params[0], params[1], params[2]);
            double majorRadius = params[3];
            double minorRadius = params[4];
            Math::Vector3D color(params[5], params[6], params[7]);
            double reflection = (params.size() > 8) ? params[8] : 0.0;

            return std::make_unique<Donut>(center, majorRadius, minorRadius, color, reflection);
        }

        return std::make_unique<Donut>();
    }

    extern "C" {
        const char *getPrimitiveName() {
            return "donut";
        }
        std::unique_ptr<IPrimitive> createPrimitive(ArgumentMap params) {
            return std::make_unique<Donut>(params);
        }
    }

}

