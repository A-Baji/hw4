#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Image.h"
#include "Scene.h"
#include "Sphere.h"
#include "Triangle.h"
using namespace std;
using namespace Raytracer148;
using namespace Eigen;

int main() {
    ofstream myfile;
    myfile.open("vectors.txt");

    Image im(400, 400);

    Scene scene;

    Vector3d center;
    center[0] = 0;
    center[1] = 0;
    center[2] = 4;
    scene.addShape(new Sphere(center, 2));

    center[0] = -.5;
    center[1] = 1;
    center[2] = 2.5;
    scene.addShape(new Sphere(center, .5));

    /*center[0] = .5;
    center[1] = 1.25;
    center[2] = 2.75;
    scene.addShape(new Sphere(center, .5));*/

    center[0] = -3;
    center[1] = 0;
    center[2] = 16;
    scene.addShape(new Sphere(center, 11));

    srand(time(NULL));
    double rando;

    Vector3d p1;
    p1[0] = 1.0;
    p1[1] = 0.8;
    p1[2] = 2.75;

    Vector3d p2;
    p2[0] = 0.2;
    p2[1] = 0.8;
    p2[2] = 2.3;

    Vector3d p3;
    p3[0] = 0.2;
    p3[1] = 1.75;
    p3[2] = 2.3;

    scene.addShape(new Triangle(p1, p2, p3));

    scene.render(im);

    im.writePNG("scene.png");

    return 0;
}
