// Reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution

#include "Triangle.h"
#include <limits>
using namespace Raytracer148;
using namespace Eigen;
using namespace std;

HitRecord Triangle::intersect(const Ray& ray) {
    HitRecord result;
    result.t = -1;

    // Calculate the normal
    Vector3d normal = ((v2 - v1).cross(v3 - v1)).normalized();

    // Check if ray and plane are parallel
    if (fabs(ray.direction.dot(normal)) < numeric_limits<double>::epsilon()) return result; // parallel, so no hit

    // Calculate distance from ray origin to interesct point
    double t = -((ray.origin - v1).dot(normal)) / (ray.direction.dot(normal));

    // Check if triangle is behind ray
    if (t < 0) return result; // no hit

    // Calculate position of intersect point
    Vector3d position = ray.origin + t * ray.direction;

    // Check if instersect is within triangle
    Vector3d C;

    // edge 1
    Vector3d edge1 = v2 - v1;
    Vector3d vp1 = position - v1;
    C = edge1.cross(vp1);
    double dist1 = C.dot(normal);
    if (dist1 < 0) return result; // no hit

    // edge 2
    Vector3d edge2 = v3 - v2;
    Vector3d vp2 = position - v2;
    C = edge2.cross(vp2);
    double dist2 = C.dot(normal);
    if (dist2 < 0) return result; // no hit

    // edge 3
    Vector3d edge3 = v1 - v3;
    Vector3d vp3 = position - v3;
    C = edge3.cross(vp3);
    double dist3 = C.dot(normal);
    if (dist3 < 0) return result; // no hit

    // Intersect is in triangle
    result.t = t;
    result.position = position;
    result.normal = normal;

    result.color[0] = 0.25;
    result.color[1] = 0.25;
    result.color[2] = 1.0;

    return result;
}