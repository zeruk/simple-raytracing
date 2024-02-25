#pragma once
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"

class Object
{
public:
  Vector3 center;
  float radius;

  Object(const Vector3 &center, float radius) : center(center), radius(radius) {}

  bool intersect(const Ray &ray) const
  {
    // Ray-sphere intersection
    Vector3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * ray.direction.dot(oc);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    return (discriminant > 0);
  }
};
