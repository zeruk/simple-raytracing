#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "./Vector3.cpp"

class Image
{
public:
    int width, height;
    std::vector<std::vector<Vector3>> pixels;

    Image(int width, int height) : width(width), height(height), pixels(width, std::vector<Vector3>(height)) {}

    bool write(const std::string &filename) const
    {
        std::ofstream file(filename.c_str());

        if (!file.is_open())
        {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
            return false;
        }

        // Write the PPM header
        file << "P3\n"
             << width << " " << height << "\n255\n";

        // Write pixel data
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                file << static_cast<int>(pixels[x][y].x * 255.0f) << " "
                     << static_cast<int>(pixels[x][y].y * 255.0f) << " "
                     << static_cast<int>(pixels[x][y].z * 255.0f) << " ";
            }
            file << "\n";
        }

        file.close();
        return true;
    }

    // Operator overloading
    Image operator+(const Image &v) const
    {
        Image image(width, height);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                image.pixels[x][y] = pixels[x][y] + v.pixels[x][y];
            }
        }

        return image;
    }

    Image operator*(const float &l) const
    {
        Image image(width, height);

        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                image.pixels[x][y] = pixels[x][y] * l;
            }
        }

        return image;
    }
};