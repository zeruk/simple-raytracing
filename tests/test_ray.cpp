#include "../src/Object.cpp"
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"
#include <iostream>

int test_ray()
{
  Object sphere = Object(Vector3(0, 0, 0), 1);
  if (!sphere.intersect(Ray(Vector3(-2, 0, 0), Vector3(1, 0, 0))))
    return 1;
  if (sphere.intersect(Ray(Vector3(-2, 0, 0), Vector3(0, 1, 0))))
    return 1;

  return 0;
}
