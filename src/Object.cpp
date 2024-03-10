#pragma once
#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Ray.cpp"
#include "../src/Materials.cpp"

class Object
{
public:
  virtual bool intersect(const Ray &ray, MaterialParameters &intersectionInfo) const = 0;
};