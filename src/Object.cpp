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
};

class Object
{
public:
  virtual bool intersect(const Ray &ray, MaterialParameters &intersectionInfo) const = 0;
};