#include "Scene.h"
#include <cmath>
using namespace Raytracer148;
using namespace std;
using namespace Eigen;

HitRecord Scene::closestHit(const Ray &ray) {
    HitRecord result;
    result.t = -1;
    bool foundSomething = false;

    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ray);
        if (r.t > std::numeric_limits<double>::epsilon() && (!foundSomething || r.t < result.t)) {
            result = r;
            foundSomething = true;
        }
    }

    return result;
}

// Returns an RGB color, where R/G/B are each in the range [0,1]
Vector3d Scene::trace(const Ray &ray) {
    // For now we'll have diffuse shading with no shadows, so it's easy!
    HitRecord r = closestHit(ray);

    Vector3d result;
    result[0] = result[1] = result[2] = 0;

    if (r.t < numeric_limits<double>::epsilon()) return result;

    Vector3d lightDir = (lightPos - r.position).normalized();

    // Create reference ray to check for shadows
    Ray ref;
    ref.origin = r.position;
    ref.direction = lightDir;

    // Check for closest hit
    for (unsigned int i = 0; i < shapes.size(); i++) {
        HitRecord r = shapes[i]->intersect(ref);

        // If something is between the position and light source, then return result as black (shadow)
        if (r.t > 0.000000000001)  return result;
    }

    double dot = lightDir.dot(r.normal);
    if (dot < 0) dot = 0;

    result = phongShading(r, lightDir, dot);

    return result;
}

void Scene::render(Image &image) {
    // We make the assumption that the camera is located at (0,0,0)
    // and that the image plane happens in the square from (-1,-1,1)
    // to (1,1,1).

    assert(image.getWidth() == image.getHeight());

    int size = image.getWidth();
    double pixelSize = 2. / size;
    for (int x = 0; x < size; x++)
        for (int y = 0; y < size; y++) {
            Ray curRay;
            curRay.origin[0] = curRay.origin[1] = curRay.origin[2] = 0;

            curRay.direction[0] = (x + 0.5) * pixelSize - 1;
            curRay.direction[1] = 1 - (y + 0.5) * pixelSize;
            curRay.direction[2] = 1;

            Vector3d color = trace(curRay);
            image.setColor(x, y, color[0], color[1], color[2]);
        }
}

Vector3d Scene::phongShading(HitRecord r, Vector3d lightDir, double dot) {
    Vector3d viewPos;
    Vector3d lightColor;
    Vector3d objectColor;

    viewPos[0] = viewPos[1] = viewPos[2] = 0;
    lightColor[0] = lightColor[1] = lightColor[2] = 1;
    objectColor[0] = dot * r.color[0];
    objectColor[1] = dot * r.color[1];
    objectColor[2] = dot * r.color[2];

    // Calculate ambient lighting by multiplying the ambient strength by the light color
    double ambientStrength = 0.1;
    Vector3d ambient = ambientStrength * lightColor;

    // Calculate the diffused lighting by getting the dot product of the normal and lightDir vectors
    Vector3d norm = r.normal;
    double diff = max(lightDir.dot(norm), 0.0);
    Vector3d diffuse = diff * lightColor;

    // Calculate the specular lighting by multiplying the reflection direction by the spec value
    double specularStrength = 0.5;
    Vector3d viewDir = (viewPos - r.position).normalized();
    Vector3d reflectDir = -lightDir - 2.0 * -lightDir.dot(norm) * norm;  // Calcultate reflection direction
    double spec = pow(max(reflectDir.dot(viewDir), 0.0), 32); // Calculate spec value
    Vector3d specular = specularStrength * spec * lightColor;

    return (ambient + diffuse + specular).cwiseProduct(objectColor);
}
