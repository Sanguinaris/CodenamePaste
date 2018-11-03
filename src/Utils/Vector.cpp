#include "Utils/Vector.h"
#include <stdexcept>
#include <type_traits>

float Vector::operator[](int idx) const {
  static_assert(std::is_standard_layout<Vector>::value,
                "Vector is not standard layout, will fuck up everything");
  switch (idx) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::logic_error{"Vector - Index out of bounds"};
  }
}

float& Vector::operator[](int idx) {
  switch (idx) {
    case 0:
      return x;
    case 1:
      return y;
    case 2:
      return z;
    default:
      throw std::logic_error{"Vector - Index out of bounds"};
  }
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
