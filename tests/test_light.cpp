#include <iostream>
#include "../src/Vector3.cpp"
#include "../src/Light.cpp"

int test_light()
{
    float epsilon = 1e-10f;

    Vector3 lightPosition(5.0f, 5.0f, 5.0f);
    Vector3 lightIntensity(1.0f, 0.0f, 10.0f);

    Light light(lightPosition, lightIntensity);

    Vector3 pointInSpace(5.0f, 5.0f, 0.0f);
    Vector3 lightDirection, lightPower;

    light.at(pointInSpace, lightDirection, lightPower);

    if (lightDirection.x != 0 || lightDirection.y != 0 || lightDirection.z != 1)
        return 1;
    if (((lightPower.x - 0.2f) > epsilon) || lightPower.y != 0.0 || ((lightPower.z - 2) > epsilon))
        return 1;

    return 0;
}
