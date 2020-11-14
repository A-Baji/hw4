#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

namespace Raytracer148 {
    class  Triangle : public Shape {
    public:
        Triangle(Eigen::Vector3d& point1, Eigen::Vector3d& point2, Eigen::Vector3d& point3) : v1(point1), v2(point2), v3(point3) {}

        virtual HitRecord intersect(const Ray& ray);

    private:
        Eigen::Vector3d v1;
        Eigen::Vector3d v2;
        Eigen::Vector3d v3;
    };
}

#endif