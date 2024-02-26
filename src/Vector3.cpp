#pragma once
#include <iostream>

class Vector3
{
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Operator overloading
    Vector3 operator+(const Vector3 &v) const
    {
        return Vector3(x + v.x, y + v.y, z + v.z);
    }
    Vector3 operator-(const Vector3 &v) const
    {
        return Vector3(x - v.x, y - v.y, z - v.z);
    }

    Vector3 operator*(const float &l) const
    {
        return Vector3(x * l, y * l, z * l);
    }

    Vector3 operator=(const Vector3 &v)
    {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        return Vector3(v.x, v.y, v.z);
    }

    float dot(const Vector3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vector3 multiplyComponents(const Vector3 &v) const
    {
        return Vector3(x * v.x, y * v.y, z * v.z);
    }

    Vector3 cross(const Vector3 &v) const
    {
        return Vector3(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x);
    }

    Vector3 normalize() const
    {
        float length = std::sqrt(x * x + y * y + z * z);
        if (length != 0.0f)
        {
            return Vector3(x / length, y / length, z / length);
        }
        else
        {
            // Return a default vector if the length is zero to avoid division by zero
            return Vector3();
        }
    }

    Vector3 clamp(float minVal, float maxVal) const
    {
        return Vector3(
            std::max(minVal, std::min(x, maxVal)),
            std::max(minVal, std::min(y, maxVal)),
            std::max(minVal, std::min(z, maxVal)));
    }

    float abs() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }

    friend std::ostream &operator<<(std::ostream &out, const Vector3 &vect)
    {
        out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
        return out;
    }
};