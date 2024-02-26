#include "../src/Object.cpp"
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"
#include <iostream>

int test_ray()
{
  MaterialParameters materialParams;
  materialParams.diffuse = Vector3(0.8f, 0.2f, 0.2f);  // Example diffuse coefficient (red)
  materialParams.specular = Vector3(0.5f, 0.5f, 0.5f); // Example specular coefficient
  materialParams.normal = Vector3(0.0f, 1.0f, 0.0f);   // Example normal vector

  Object sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, materialParams);

  Ray ray(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));

  MaterialParameters intersectionInfo;
  bool intersects = sphere.intersect(ray, intersectionInfo);

  if (intersects)
  {
    return 0;
    std::cout << "Intersection Point: " << intersectionInfo.intersectionPoint << std::endl;
    std::cout << "Normal Vector: " << intersectionInfo.normal << std::endl;
    std::cout << "Diffuse Coefficient: " << intersectionInfo.diffuse << std::endl;
    std::cout << "Specular Coefficient: " << intersectionInfo.specular << std::endl;
  }
  else
  {
    return 1;
    std::cout << "No intersection." << std::endl;
  }
}
