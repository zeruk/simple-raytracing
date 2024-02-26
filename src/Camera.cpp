#pragma once
#include <iostream>
#include <cstdlib>
#include "./Vector3.cpp"
#include "./Ray.cpp"

class Camera
{
public:
  float focalLength;
  // Calculate the direction vector from the camera to the pixel on the image plane
  Vector3 position;
  Vector3 forward;
  Vector3 right;
  Vector3 upAdjusted;
  int sizeX;
  int sizeY;

  Camera(float focalLength, const Vector3 &position, const Vector3 &target, const Vector3 &up, int sizeX, int sizeY, int randomSeed)
      : focalLength(focalLength), position(position), sizeX(sizeX), sizeY(sizeY)
  {
    forward = (target - position).normalize();
    right = forward.cross(up.normalize()).normalize();
    upAdjusted = right.cross(forward).normalize();

    srand(static_cast<unsigned>(randomSeed));

    std::cout << "__Camera__: position=" << position
              << "; target=" << target
              << "; up=" << up
              << "; forward=" << forward
              << "; right=" << right
              << "; upAdjusted=" << upAdjusted
              << "; random=" << getRandom()
              << "; sensorX(1)=" << static_cast<float>(1) / sizeX
              << std::endl;
  }

  // generates numbers in range [-0.0001,0.0001]
  float getRandom() const
  {
    const float LO = -0.0001;
    const float HI = -LO;
    return LO + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (HI - LO)));
  }

  Ray pixelToRay(int pixelX, int pixelY) const
  {
    float sensorX = static_cast<float>(pixelX) / sizeX;
    float sensorY = static_cast<float>(pixelY) / sizeY;

    Vector3 pixelDirection =
        forward * focalLength +
        right * (sensorX + getRandom()) +
        upAdjusted * (sensorY + getRandom());

    // std::cout << "__Camera__: pixelX=" << pixelX
    //           << "; pixelY=" << pixelY
    //           << "; sensorX=" << sensorX
    //           << "; sensorY=" << sensorY
    //           << "; right=" << right * sensorX
    //           << "; up=" << upAdjusted * sensorY
    //           << "; fin=" << pixelDirection
    //           << std::endl;

    return Ray(position, pixelDirection.normalize());
  }
};