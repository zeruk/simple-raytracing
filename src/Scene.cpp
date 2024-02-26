#pragma once
#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Light.cpp"
#include "../src/Image.cpp"
#include "../src/Object.cpp"
#include "../src/Camera.cpp"

class Scene
{
public:
  std::vector<Light> lights;
  std::vector<Object> objects;
  Camera camera;

  Scene(const Camera &camera, const std::vector<Light> &lights, const std::vector<Object> &objects) : camera(camera), lights(lights), objects(objects) {}

  // Method to add a new light to the scene
  void addLight(const Light &light)
  {
    lights.push_back(light);
  }

  Image render(int width, int height)
  {
    Image image(width, height);

    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        // Map pixel coordinates to ray
        Ray ray = camera.pixelToRay(x - (width / 2), y - (height / 2));

        // Check for intersections with objects in the scene
        bool intersection = false;
        MaterialParameters intersectionInfo;

        for (const Object &object : objects)
        {
          if (object.intersect(ray, intersectionInfo))
          {
            intersection = true;
            break; // Stop at the first intersection
          }
        }

        // Set pixel color based on intersection
        if (intersection)
        {
          image.pixels[x][y] = Vector3(1.0f, 1.0f, 1.0f); // White color for intersection
        }
        else
        {
          image.pixels[x][y] = Vector3(0.0f, 0.0f, 0.0f); // Black color for no intersection
        }
      }
    }

    return image;
  }
};
