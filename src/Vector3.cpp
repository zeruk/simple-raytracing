#include <iostream>
#pragma once

class Vector3
{
public:
    float x, y, z;

    // Constructors
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Operator overloading
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

    friend std::ostream &operator<<(std::ostream &out, const Vector3 &vect)
    {
        out << "(" << vect.x << ", " << vect.y << ", " << vect.z << ")";
        return out;
    }
};