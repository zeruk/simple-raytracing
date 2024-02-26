#pragma once
#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"

struct MaterialParameters
{
  Vector3 diffuse;  // Diffuse coefficient
  Vector3 specular; // Specular coefficient
  Vector3 normal;
  Vector3 intersectionPoint;
  // Add more material-related parameters as needed
};

class Object
{
public:
  Vector3 center;
  float radius;
  MaterialParameters material;

  Object(const Vector3 &center, float radius, const MaterialParameters &material)
      : center(center), radius(radius), material(material) {}

  bool intersect(const Ray &ray, MaterialParameters &intersectionInfo) const
  {
    // Ray-sphere intersection
    Vector3 oc = ray.origin - center;
    float a = ray.direction.dot(ray.direction);
    float b = 2.0f * ray.direction.dot(oc);
    float c = oc.dot(oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;

    // std::cout << "ray.origin=" << ray.origin << "ray.direction=" << ray.direction << ", sphere center =" << center << ", radius=" << radius << std::endl;
    if (discriminant > 0)
    {
      // Calculate intersection point and normal
      float t1 = (-b - std::sqrt(discriminant)) / (2.0f * a);
      float t2 = (-b + std::sqrt(discriminant)) / (2.0f * a);
      float t = (t1 < t2) ? t1 : t2;
      if (t < 0)
        return false;

      intersectionInfo.intersectionPoint = ray.origin + ray.direction * t;
      intersectionInfo.normal = (intersectionInfo.intersectionPoint - center).normalize();

      // Set material properties
      intersectionInfo.diffuse = material.diffuse;
      intersectionInfo.specular = material.specular;

      return true;
    }
    return false;
  }
};
