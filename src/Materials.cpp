#pragma once
#include "../src/Vector3.cpp"

struct MaterialParameters
{
  Vector3 diffuse;  // Diffuse coefficient
  Vector3 specular; // Specular coefficient
  Vector3 normal;
  Vector3 intersectionPoint;
};
const Vector3 StandardSpecular = Vector3(0.999f, 0.999f, 0.999f);

const MaterialParameters MATERIAL_RED = {
    Vector3(0.8f, 0.2f, 0.2f),
    StandardSpecular};
const MaterialParameters MATERIAL_GREEN = {
    Vector3(0.2f, 0.8f, 0.2f),
    StandardSpecular};
const MaterialParameters MATERIAL_BLUE = {
    Vector3(0.2f, 0.2f, 0.8f),
    StandardSpecular};
const MaterialParameters MATERIAL_GRAY = {
    Vector3(1.0f, 1.0f, 1.0f),
    StandardSpecular};