#include <iostream>
#include <fstream>
#include <chrono>
#include "./Vector3.cpp"
#include "./Materials.cpp"
#include "./Image.cpp"
#include "./Camera.cpp"
#include "./Sphere.cpp"
#include "./OriginMarker.cpp"
#include "./Plane.cpp"
#include "./Scene.cpp"

const int RENDERS = 5;
const int RAY_BOUNCES = 3;

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

    std::vector<Object *> objects;
    // objects.push_back(new Sphere(Vector3(1.0f, -2.0f, -2.0f), 1.0f, MATERIAL_GREEN));
    // objects.push_back(new Sphere(Vector3(0.0f, 0.0f, -2.0f), 1.0f, MATERIAL_RED));
    // objects.push_back(new Sphere(Vector3(-1.0f, 1.0f, -4.0f), 1.0f, MATERIAL_GREEN));
    // objects.push_back(new Sphere(Vector3(0.5f, -0.5f, -3.0f), 1.0f, MATERIAL_GRAY));
    objects.push_back(new OriginMarker(Vector3(2, 2, 0), 0.3f));
    // objects.push_back(new Plane(Vector3(0.3f, 0.3f, 0.3f), -10.0f, MATERIAL_BLUE));

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
