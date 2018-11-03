#pragma once

class Vector {
 public:
  float x = 0.f, y = 0.f, z = 0.f;

  float operator[](int idx) const;

  float& operator[](int idx);

  bool operator==(const Vector& otherVec) const;

  bool operator!=(const Vector& otherVec) const;

  Vector& operator+=(const Vector& otherVec);

  Vector& operator-=(const Vector& otherVec);

  Vector operator-(const Vector& otherVec) const;

  Vector operator+(const Vector& otherVec) const;
};