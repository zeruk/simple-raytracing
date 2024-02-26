#pragma once
#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"
#include "../src/Object.cpp"

class Plane : public Object
{
public:
  Vector3 normal;
  float distance;                    // Distance from the origin along the normal vector
  MaterialParameters materialParams; // normal doesn't matter here

  Plane(const Vector3 &normal, float distance, const MaterialParameters &materialParams)
      : normal(normal.normalize()), distance(distance), materialParams(materialParams) {}

  bool intersect(const Ray &ray, MaterialParameters &intersectionInfo) const override
  {
    float denom = normal.dot(ray.direction);

    // Check if the ray is parallel or nearly parallel to the plane
    if (std::abs(denom) > 1e-6)
    {
      float t = (distance - normal.dot(ray.origin)) / denom;

      if (t >= 0)
      {
        // Intersection found, populate intersectionInfo
        intersectionInfo.intersectionPoint = ray.origin + ray.direction * t;
        intersectionInfo.normal = normal;
        intersectionInfo.diffuse = materialParams.diffuse;
        intersectionInfo.specular = materialParams.specular;

        return true;
      }
    }

    return false; // No intersection
  }
};
