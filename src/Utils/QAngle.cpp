#include "Utils/QAngle.h"
#include <stdexcept>
#include <type_traits>

using namespace CodeNamePaste;
using namespace Utils;

QAngle::QAngle(float* vec) : vec{vec}, x{vec[0]}, y{vec[1]} {}

QAngle::QAngle(float vecX, float vecY, float vecZ)
    : vec{std::make_unique<float[]>(3)}, x{vec[0]}, y{vec[1]} {
  vec[0] = vecX;
  vec[1] = vecY;
  vec[2] = vecZ;
}

float QAngle::operator[](int idx) const {
  return vec[idx];
}

float& QAngle::operator[](int idx) {
  return vec[idx];
}

bool QAngle::operator==(const QAngle& otherVec) const {
  return x == otherVec.x && y == otherVec.y && vec[2] == otherVec.vec[2];
}

bool QAngle::operator!=(const QAngle& otherVec) const {
  return !operator==(otherVec);
}

QAngle& QAngle::operator+=(const QAngle& otherVec) {
  x += otherVec.x;
  y += otherVec.y;
  vec[2] += otherVec[2];
  return *this;
}

QAngle& QAngle::operator-=(const QAngle& otherVec) {
  x -= otherVec.x;
  y -= otherVec.y;
  vec[2] -= otherVec.vec[2];
  return *this;
}

QAngle QAngle::operator-(const QAngle& otherVec) const {
  return {x - otherVec.x, y - otherVec.y, vec[2] - otherVec.vec[2]};
}

QAngle QAngle::operator+(const QAngle& otherVec) const {
  return {x + otherVec.x, y + otherVec.y, vec[2] + otherVec.vec[2]};
}

QAngle& QAngle::operator=(QAngle&& otherVec) {
    vec = std::move(otherVec.vec);
    x = vec[0];
    y = vec[1];
    return *this;
  };
