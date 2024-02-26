#include <iostream>
#include <fstream>
#include "../src/Vector3.cpp"
#include "./Image.cpp"
#include "./Camera.cpp"
#include "./Object.cpp"
#include "./Scene.cpp"

int main()
{
    int imageWidth = 300;
    int imageHeight = 300;

    // CAMERA
    Vector3 cameraPosition(0.0f, 0.0f, 5.0f);
    Vector3 targetPoint(0.0f, 0.0f, -1.0f);
    Vector3 upVector(0.0f, 1.0f, 0.0f);
    Camera camera(1.0f, cameraPosition, targetPoint, upVector, imageWidth, imageHeight);

    // LIGHTS
    Vector3 lightPosition(5.0f, 5.0f, 5.0f);
    Vector3 lightIntensity(1.0f, 0.0f, 10.0f);

    Light light1(lightPosition, lightIntensity);
    std::vector<Light> lights = {light1};

    // SPHERES
    MaterialParameters materialParams;
    materialParams.kd = Vector3(0.8f, 0.2f, 0.2f);     // Example diffuse coefficient (red)
    materialParams.ks = Vector3(0.5f, 0.5f, 0.5f);     // Example specular coefficient
    materialParams.normal = Vector3(0.0f, 1.0f, 0.0f); // Example normal vector

    Object sphere0(Vector3(0.0f, 0.0f, 0.0f), 1.0f, materialParams);
    Object sphere1(Vector3(1.0f, -1.5f, -2.0f), 1.0f, materialParams);
    Object sphere2(Vector3(-1.0f, 1.0f, -4.0f), 1.0f, materialParams);
    std::vector<Object> objects = {sphere0, sphere1, sphere2};

    // SCENE
    Scene scene(camera, lights, objects);

    Image resultImage = scene.render(imageWidth, imageHeight);

    // Save the result image to a file (you can use the Image write method from previous implementations)
    resultImage.write("rendered_image.ppm");

    return 0;
}
