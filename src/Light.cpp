#pragma once
#include <iostream>
#include "../src/Vector3.cpp"

class Light
{
public:
  Vector3 position;
  Vector3 intensity;

  Light(const Vector3 &position, const Vector3 &intensity) : position(position), intensity(intensity) {}

  void at(const Vector3 &point, Vector3 &direction, Vector3 &power) const
  {
    Vector3 pp_distance = position - point;
    float length = std::sqrt(pp_distance.x * pp_distance.x + pp_distance.y * pp_distance.y + pp_distance.z * pp_distance.z);

    // Calculate direction from the point to the light source
    direction = pp_distance.normalize();

    // Set the power/intensity of the light
    power = intensity * (1.0 / length);
  }
};
