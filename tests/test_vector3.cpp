#include <iostream>
#include "../src/Vector3.cpp"

int test_vector3() {
    Vector3 v1(1.0f, 2.0f, 3.0f);
    Vector3 v2 = v1 * 2.0f;

    std::cout << "Original Vector: " << v1 << std::endl;
    std::cout << "Scaled Vector: " << v2 << std::endl;

    // Add more test cases as needed

    return 0;
}
