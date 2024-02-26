#include "../src/Object.cpp"
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"
#include <iostream>

int test_ray()
{
  MaterialParameters materialParams;
  materialParams.kd = Vector3(0.8f, 0.2f, 0.2f);     // Example diffuse coefficient (red)
  materialParams.ks = Vector3(0.5f, 0.5f, 0.5f);     // Example specular coefficient
  materialParams.normal = Vector3(0.0f, 1.0f, 0.0f); // Example normal vector

  Object sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, materialParams);

  Ray ray(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));

  MaterialParameters intersectionInfo;
  bool intersects = sphere.intersect(ray, intersectionInfo);

  if (intersects)
  {
    std::cout << "Intersection Point: " << intersectionInfo.intersectionPoint << std::endl;
    std::cout << "Normal Vector: " << intersectionInfo.normal << std::endl;
    std::cout << "Diffuse Coefficient: " << intersectionInfo.kd << std::endl;
    std::cout << "Specular Coefficient: " << intersectionInfo.ks << std::endl;
  }
  else
  {
    std::cout << "No intersection." << std::endl;
  }
  return 0;
}
