#include "../src/Sphere.cpp"
#include "../src/Plane.cpp"
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"
#include <iostream>

int test_ray()
{
  Sphere sphere(Vector3(0.0f, 0.0f, 0.0f), 1.0f, MATERIAL_RED);

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

  std::cout << "Testing plane";
  // PLANE
  Plane plane(Vector3(0.0f, 1.0f, 0.0f), -1, MATERIAL_RED);
  // intersecting
  Ray ray3(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
  if (!plane.intersect(ray3, intersectionInfo))
  {
    std::cout << "No intersection 3!";
    return 1;
  }
  Ray ray31(Vector3(0.0f, 1.1f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
  if (!plane.intersect(ray31, intersectionInfo))
  {
    std::cout << "No intersection 31!";
    return 1;
  }
  Ray ray32(Vector3(0.0f, -1.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
  if (!plane.intersect(ray32, intersectionInfo))
  {
    std::cout << "No intersection 32!";
    return 1;
  }
  Ray ray33(Vector3(0.0f, -1.001f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
  if (plane.intersect(ray33, intersectionInfo))
  {
    std::cout << "Intersection 33!";
    return 1;
  }
  // intersecting, but behind plane => not intersecting
  Ray ray4(Vector3(0.0f, -2.0f, 0.0f), Vector3(0.0f, -1.0f, 0.0f));
  if (plane.intersect(ray4, intersectionInfo))
  {
    std::cout << "Intersect 4! intersection point:" << intersectionInfo.intersectionPoint;
    return 1;
  }
  // intersecting, but in opposite direction => not intersecting
  Ray ray5(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, 1.0f, 0.0f));
  if (plane.intersect(ray5, intersectionInfo))
  {
    std::cout << "Intersect 5! intersection point:" << intersectionInfo.intersectionPoint;
    return 1;
  }

  return 0;
}
