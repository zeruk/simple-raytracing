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

  // should intersect
  if (!intersects)
    return 1;

  Ray ray1(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, 0.0f, 1.0f));

  // should NOT intersect
  if (sphere.intersect(ray1, intersectionInfo))
  {
    std::cout << "Intersect! intersection point:" << intersectionInfo.intersectionPoint;
    return 1;
  }

  // intersecting, but in opposite direction
  Ray ray2(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));

  // should NOT intersect
  if (sphere.intersect(ray2, intersectionInfo))
  {
    std::cout << "Intersect! intersection point:" << intersectionInfo.intersectionPoint;
    return 1;
  }

  return 0;
}
