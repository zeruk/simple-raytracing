#include <iostream>
#include "../src/Vector3.cpp"

int test_vector3()
{
    // test 1
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2 = v1 * 2.0f;

    if (v2.x != 2.0f || v2.y != 4.0f || v2.z != 6.0f)
        return 1;

    // test 2
    Vector3 v3(1.0f, 2.0f, 3.0f);
    Vector3 v4(4.0f, 5.0f, 6.0f);

    float dotProduct = v3.dot(v4);

    if (dotProduct != 32)
        return 1;

    return 0;
}
