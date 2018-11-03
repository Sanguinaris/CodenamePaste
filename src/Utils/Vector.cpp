#include "Utils/Vector.h"
#include <stdexcept>
#include <type_traits>

using namespace CodeNamePaste;
using namespace Utils;

Vector::Vector(float* vec) : vec{vec}, x{vec[0]}, y{vec[1]}, z{vec[2]} {}

Vector::Vector(float vecX, float vecY, float vecZ)
    : vec{std::make_unique<float[]>(3)}, x{vec[0]}, y{vec[1]}, z{vec[2]} {
  vec[0] = vecX;
  vec[1] = vecY;
  vec[2] = vecZ;
}

float Vector::operator[](int idx) const {
  return vec[idx];
}

float& Vector::operator[](int idx) {
  return vec[idx];
}

bool Vector::operator==(const Vector& otherVec) const {
  return x == otherVec.x && y == otherVec.y && z == otherVec.z;
}

bool Vector::operator!=(const Vector& otherVec) const {
  return !operator==(otherVec);
}

Vector& Vector::operator+=(const Vector& otherVec) {
  x += otherVec.x;
  y += otherVec.y;
  z += otherVec.z;
  return *this;
}

Vector& Vector::operator-=(const Vector& otherVec) {
  x -= otherVec.x;
  y -= otherVec.y;
  z -= otherVec.z;
  return *this;
}

Vector Vector::operator-(const Vector& otherVec) const {
  return {x - otherVec.x, y - otherVec.y, z - otherVec.z};
}

Vector Vector::operator+(const Vector& otherVec) const {
  return {x + otherVec.x, y + otherVec.y, z + otherVec.z};
}
