#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Light.cpp"

class Scene
{
public:
  std::vector<Light> lights;

  // Add other scene-related properties and methods as needed

  Scene(const std::vector<Light> &lights) : lights(lights) {}

  // Method to add a new light to the scene
  void addLight(const Light &light)
  {
    lights.push_back(light);
  }
};
