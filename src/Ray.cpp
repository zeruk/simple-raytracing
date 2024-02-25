#pragma once
#include <cmath>
#include "../src/Vector3.cpp"

class Ray
{
public:
  Vector3 origin;
  Vector3 direction;

  Ray(const Vector3 &origin, const Vector3 &direction) : origin(origin), direction(direction) {}
};