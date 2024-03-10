#pragma once
#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Object.cpp"
#include "../src/Sphere.cpp"

const float ORIGIN_SPHERE_RADIUS_COEF = 0.3f;
class OriginMarker : public Object
{
  Vector3 center;
  Sphere *o, *x, *y, *z;

public:
  OriginMarker(const Vector3 &center, float radius)
      : center(center)
  {
    o = new Sphere(Vector3(center.x, center.y, center.z), ORIGIN_SPHERE_RADIUS_COEF * radius, MATERIAL_GRAY);
    x = new Sphere(Vector3(center.x - radius, center.y, center.z), ORIGIN_SPHERE_RADIUS_COEF * radius, MATERIAL_RED);
    y = new Sphere(Vector3(center.x, center.y - radius, center.z), ORIGIN_SPHERE_RADIUS_COEF * radius, MATERIAL_GREEN);
    z = new Sphere(Vector3(center.x, center.y, center.z - radius), ORIGIN_SPHERE_RADIUS_COEF * radius, MATERIAL_BLUE);
  }

  bool intersect(const Ray &ray, MaterialParameters &intersectionInfo) const override
  {
    MaterialParameters intersectionInfoInternal;
    if (o->intersect(ray, intersectionInfoInternal))
    {
      intersectionInfo = intersectionInfoInternal;
      return true;
    }
    if (x->intersect(ray, intersectionInfoInternal))
    {
      intersectionInfo = intersectionInfoInternal;
      return true;
    }
    if (y->intersect(ray, intersectionInfoInternal))
    {
      intersectionInfo = intersectionInfoInternal;
      return true;
    }
    if (z->intersect(ray, intersectionInfoInternal))
    {
      intersectionInfo = intersectionInfoInternal;
      return true;
    }
    return false;
  }
};