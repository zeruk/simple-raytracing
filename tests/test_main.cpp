#include "./test_image.cpp"
#include "./test_vector3.cpp"
#include "./test_ray.cpp"
#include "./test_light.cpp"
#include <iostream>

int main()
{
  std::cout << "Test" << std::endl;
  int res = test_image() || test_vector3() || test_ray() || test_light();
  return res;
}