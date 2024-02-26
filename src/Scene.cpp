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
          }        // TODO: Choose closest one
        }

        // Set pixel color based on intersection
        if (intersection)
        {
          image.pixels[x][y] = Vector3(0.0f, 0.0f, 0.0f);
          for (const Light &light : lights)
          {
            Vector3 lightDirection, lightPower;
            light.at(intersectionInfo.intersectionPoint, lightDirection, lightPower);

            float dotProduct = std::max(0.0f, intersectionInfo.normal.dot(lightDirection));
            if (dotProduct > 0.0f)
            {
              Vector3 diffuseContribution = intersectionInfo.diffuse.multiplyComponents(lightPower) * dotProduct;
              image.pixels[x][y] = image.pixels[x][y] + diffuseContribution;
            }
          }
          image.pixels[x][y] = image.pixels[x][y].clamp(0.0f, 1.0f);
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
