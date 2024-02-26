#include <iostream>
#include <fstream>
#include "../src/Vector3.cpp"
#include "./Image.cpp"
#include "./Camera.cpp"
#include "./Sphere.cpp"
#include "./Scene.cpp"

int main()
{
    int imageWidth = 512;
    int imageHeight = 512;

    // CAMERA
    Vector3 cameraPosition(0.0f, 0.0f, 5.0f);
    Vector3 targetPoint(0.0f, 0.0f, -1.0f);
    Vector3 upVector(1.0f, 0.0f, 0.0f);
    Camera camera(1.0f, cameraPosition, targetPoint, upVector, imageWidth, imageHeight);

    // LIGHTS
    std::vector<Light> lights = {
        // position, intencity
        Light(Vector3(5.0f, 5.0f, 5.0f), Vector3(4.0f, 4.0f, 4.0f)),
        Light(Vector3(5.0f, -6.0f, 0.0f), Vector3(5.0f, 5.0f, 5.0f))
        //
    };

    // SPHERES
    MaterialParameters materialRed;
    materialRed.diffuse = Vector3(0.8f, 0.2f, 0.2f);
    materialRed.specular = Vector3(0.8f, 0.8f, 0.8f);
    materialRed.normal = Vector3(0.0f, 1.0f, 0.0f);
    MaterialParameters materialGreen;
    materialGreen.diffuse = Vector3(0.2f, 0.8f, 0.2f);
    materialGreen.specular = Vector3(0.25f, 0.25f, 0.25f);
    materialGreen.normal = Vector3(0.0f, 1.0f, 0.0f);

    std::vector<Object *> objects;
    objects.push_back(new Sphere(Vector3(1.0f, -2.0f, -2.0f), 1.0f, materialGreen));
    objects.push_back(new Sphere(Vector3(0.0f, 0.0f, -2.0f), 1.0f, materialRed));
    objects.push_back(new Sphere(Vector3(-1.0f, 1.0f, -4.0f), 1.0f, materialGreen));

    // SCENE
    Scene scene(camera, lights, objects);

    Image resultImage = scene.render(imageWidth, imageHeight, 5);

    // Save the result image to a file (you can use the Image write method from previous implementations)
    resultImage.write("rendered_image.ppm");

    return 0;
}
