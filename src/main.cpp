#include <iostream>
#include <fstream>
#include <chrono>
#include "../src/Vector3.cpp"
#include "./Image.cpp"
#include "./Camera.cpp"
#include "./Sphere.cpp"
#include "./Plane.cpp"
#include "./Scene.cpp"

const int RENDERS = 1;
const int RAY_BOUNCES = 5;

int main()
{
    int imageWidth = 500;
    int imageHeight = 500;

    // CAMERA
    Vector3 cameraPosition(0.0f, 0.0f, 5.0f);
    Vector3 targetPoint(0.0f, 0.0f, -1.0f);
    Vector3 upVector(1.0f, 0.0f, 0.0f);
    Camera camera(1.0f, cameraPosition, targetPoint, upVector, imageWidth, imageHeight, 111);

    // LIGHTS
    std::vector<Light> lights = {
        // position, intencity
        Light(Vector3(5.0f, 5.0f, 5.0f), Vector3(4.0f, 4.0f, 4.0f)),
        Light(Vector3(5.0f, -6.0f, 3.0f), Vector3(5.0f, 5.0f, 5.0f))
        //
    };

    // SPHERES
    MaterialParameters materialRed;
    materialRed.diffuse = Vector3(0.8f, 0.2f, 0.2f);
    materialRed.specular = Vector3(0.999f, 0.999f, 0.999f);
    materialRed.normal = Vector3(0.0f, 1.0f, 0.0f);
    MaterialParameters materialGreen;
    materialGreen.diffuse = Vector3(0.2f, 0.8f, 0.2f);
    materialGreen.specular = Vector3(0.25f, 0.25f, 0.25f);
    materialGreen.normal = Vector3(0.0f, 1.0f, 0.0f);
    MaterialParameters materialBlue;
    materialBlue.diffuse = Vector3(0.2f, 0.2f, 0.8f);
    materialBlue.specular = Vector3(0.3f, 0.3f, 0.6f);
    materialBlue.normal = Vector3(0.0f, 1.0f, 0.0f);
    MaterialParameters materialGray;
    materialGray.diffuse = Vector3(1.0f, 1.0f, 1.0f);
    materialGray.specular = Vector3(1.0f, 1.0f, 1.0f);
    materialGray.normal = Vector3(0.0f, 1.0f, 0.0f);

    std::vector<Object *> objects;
    objects.push_back(new Sphere(Vector3(1.0f, -2.0f, -2.0f), 1.0f, materialGreen));
    objects.push_back(new Sphere(Vector3(0.0f, 0.0f, -2.0f), 1.0f, materialRed));
    objects.push_back(new Sphere(Vector3(-1.0f, 1.0f, -4.0f), 1.0f, materialGreen));
    objects.push_back(new Sphere(Vector3(0.5f, -0.5f, -3.0f), 1.0f, materialGray));
    objects.push_back(new Plane(Vector3(0.3f, 0.3f, 0.3f), -10.0f, materialBlue));

    // SCENE
    Scene scene(camera, lights, objects);

    Image resultImage(imageWidth, imageHeight);
    // initial render
    for (size_t i = 0; i < RENDERS; i++)
    {
        auto start = std::chrono::high_resolution_clock::now();
        resultImage = resultImage + scene.render(imageWidth, imageHeight, RAY_BOUNCES) * (1.0f / RENDERS);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

        std::cout << "Done " << i + 1 << "/" << RENDERS
                  << " renders. (Time: "
                  << duration.count() / 1000 << "ms)"
                  << std::endl;
    }

    // Save the result image to a file (you can use the Image write method from previous implementations)
    resultImage.write("rendered_image.ppm");

    // Cleanup: Delete allocated objects
    for (Object *obj : objects)
    {
        delete obj;
    }

    return 0;
}
