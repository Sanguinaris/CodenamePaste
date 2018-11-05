#pragma once
#include <memory>

namespace CodeNamePaste {
namespace Utils {
class Vector {
 public:
  Vector(float* vecPtr);

  Vector(float x = 0.f, float y = 0.f, float z = 0.f);

  Vector(Vector&&) = default;

 public:
  float operator[](int idx) const;

  float& operator[](int idx);

  bool operator==(const Vector& otherVec) const;

  bool operator!=(const Vector& otherVec) const;

  Vector& operator+=(const Vector& otherVec);

  Vector& operator-=(const Vector& otherVec);

  Vector operator-(const Vector& otherVec) const;

  Vector operator+(const Vector& otherVec) const;

  Vector& operator=(Vector&& otherVec) {
    vec = std::move(otherVec.vec);
    x = vec[0];
    y = vec[1];
    z = vec[2];
    return *this;
  };

 private:
  std::unique_ptr<float[]> vec;

 public:
  std::reference_wrapper<float> x;
  std::reference_wrapper<float> y;
  std::reference_wrapper<float> z;
};
}  // namespace Utils
}  // namespace CodeNamePaste
