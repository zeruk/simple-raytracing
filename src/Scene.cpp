#pragma once
#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Light.cpp"
#include "../src/Image.cpp"
#include "../src/Object.cpp"
#include "../src/Camera.cpp"

class Scene
{
public:
  std::vector<Light> lights;
  std::vector<Object *> objects;
  Camera camera;

  Scene(const Camera &camera, const std::vector<Light> &lights, const std::vector<Object *> &objects) : camera(camera), lights(lights), objects(objects) {}

  Image render(int width, int height, int reflectionDepth)
  {
    Image image(width, height);

    for (int y = 0; y < height; ++y)
    {
      for (int x = 0; x < width; ++x)
      {
        // Map pixel coordinates to ray
        Ray ray = camera.pixelToRay(x - (width / 2), y - (height / 2));

        image.pixels[x][y] = renderRay(ray, reflectionDepth);
      }
    }

    return image;
  }

  Vector3 renderRay(Ray ray, int reflectionDepth)
  {

    // Check for intersections with objects in the scene
    bool intersection = false;
    MaterialParameters intersectionInfo, closestIntersection;

    for (const auto &object : objects)
    {
      if (object->intersect(ray, intersectionInfo))
      {
        if (!intersection)
          closestIntersection = intersectionInfo;
        intersection = true;

        if ((closestIntersection.intersectionPoint - camera.position).abs() >
            (intersectionInfo.intersectionPoint - camera.position).abs())
        {
          std::swap(closestIntersection, intersectionInfo);
        }
        // Choose closest one
      }
    }

    // Set pixel color based on intersection
    if (intersection)
    {
      Vector3 totalDiffuse(0.0f, 0.0f, 0.0f);
      Vector3 totalSpecular(0.0f, 0.0f, 0.0f);
      for (const Light &light : lights)
      {
        // Check if the point is in shadow
        if (!isPointInShadow(closestIntersection.intersectionPoint, light))
        {
          Vector3 lightDirection, lightPower;
          light.at(closestIntersection.intersectionPoint, lightDirection, lightPower);

          float dotProduct = std::max(0.0f, closestIntersection.normal.dot(lightDirection));
          if (dotProduct > 0.0f)
          {
            Vector3 diffuseContribution = closestIntersection.diffuse.multiplyComponents(lightPower) * dotProduct;
            totalDiffuse = totalDiffuse + diffuseContribution;
          }

          // Specular reflection model (Phong reflection model)
          Vector3 reflectedDirection = closestIntersection.normal * (lightDirection.dot(closestIntersection.normal)) * 2.0f - lightDirection;
          float dotProductSpecular = std::max(0.0f, ray.direction.dot(reflectedDirection));
          Vector3 specularContribution = closestIntersection.specular.multiplyComponents(lightPower) * std::pow(dotProductSpecular, 32);

          totalSpecular = totalSpecular + specularContribution;
        }
      }
      // Ambient reflection model
      Vector3 ambientColor(0.1f, 0.1f, 0.1f); // Ambient color for the scene
      Vector3 ambientContribution = ambientColor.multiplyComponents(closestIntersection.diffuse);

      // Reflection contribution
      Vector3 reflectionContribution = calculateReflectionContribution(ray, intersectionInfo, reflectionDepth);

      // Total lighting (diffuse + specular + ambient)
      Vector3 totalLighting = totalDiffuse + totalSpecular + reflectionContribution + ambientContribution;
      return totalLighting.clamp(0.0f, 1.0f);
    }
    else
    {
      return Vector3(0.0f, 0.0f, 0.0f); // Black color for no intersection
    }
  }

  bool isPointInShadow(const Vector3 &point, const Light &light)
  {
    Ray shadowRay(point, (light.position - point).normalize());

    // Check for intersections with objects in the scene
    for (const auto &object : objects)
    {
      MaterialParameters shadowIntersectionInfo;
      if (object->intersect(shadowRay, shadowIntersectionInfo))
      {
        // std::cout << object.center;
        // If there is an intersection with any object, the point is in shadow
        return true;
      }
    }
    // If no intersections are found, the point is not in shadow
    return false;
  }

  Vector3 calculateReflectionContribution(const Ray &ray, const MaterialParameters &intersectionInfo, int reflectionDepth)
  {
    if (reflectionDepth <= 0)
    {
      return Vector3(0.0f, 0.0f, 0.0f); // No more reflections, return black
    }

    // Calculate reflection direction
    Vector3 reflectedDirection = ray.direction - intersectionInfo.normal * 2.0f * (ray.direction.dot(intersectionInfo.normal));

    // Create a reflected ray
    Ray reflectedRay(intersectionInfo.intersectionPoint, reflectedDirection);

    // Recursively compute illumination on the reflected ray
    Vector3 reflectedIllumination = renderRay(reflectedRay, reflectionDepth - 1);

    // Apply specular coefficient and add to the total reflection contribution
    Vector3 reflectionContribution = intersectionInfo.specular.multiplyComponents(reflectedIllumination);

    return reflectionContribution;
  }
};
