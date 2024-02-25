#include <iostream>
#include <fstream>
#include "../src/Vector3.cpp"
#include "../src/Image.cpp"

int test_image()
{
  // Example: Create an image with a simple gradient
  const int width = 512;
  const int height = 512;

  Image gradientImage(width, height);

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      float r = static_cast<float>(x) / static_cast<float>(width);
      float g = static_cast<float>(y) / static_cast<float>(height);
      float b = 0.5f; // Constant blue component
      gradientImage.pixels[x][y] = Vector3(r, g, b);
    }
  }

  // Save the image to a file
  gradientImage.write("gradient_image.ppm");

  return 0;
}
