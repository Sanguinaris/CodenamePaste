#pragma once
#include <memory>

namespace CodeNamePaste {
namespace Utils {
class QAngle {
 public:
  QAngle(float* vecPtr);

  QAngle(float x = 0.f, float y = 0.f, float z = 0.f);

  QAngle(QAngle&&) = default;

 public:
  float operator[](int idx) const;

  float& operator[](int idx);

  bool operator==(const QAngle& otherVec) const;

  bool operator!=(const QAngle& otherVec) const;

  QAngle& operator+=(const QAngle& otherVec);

  QAngle& operator-=(const QAngle& otherVec);

  QAngle operator-(const QAngle& otherVec) const;

  QAngle operator+(const QAngle& otherVec) const;

  QAngle& operator=(QAngle&& otherVec);

 private:
  std::unique_ptr<float[]> vec;

 public:
  std::reference_wrapper<float> x;
  std::reference_wrapper<float> y;
};
}  // namespace Utils
}  // namespace CodeNamePaste
