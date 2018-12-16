#pragma once
#include <cmath>
#include <iostream>
#include <memory>

// Credz to notphage
namespace CodeNamePaste {
namespace Utils {

class Vector2 {
 public:
  float x, y;

  constexpr explicit Vector2(float _x = 0.f, float _y = 0.f) : x{_x}, y{_y} {}

  constexpr explicit Vector2(const float* v) : x{v[0]}, y{v[1]} {}

  constexpr auto empty() const { return x == 0.f && y == 0.f; }

  constexpr auto clear() {
    x = 0.f;
    y = 0.f;
  }

  constexpr auto operator==(const Vector2& other) const {
    return (x == other.x && y == other.y);
  }

  constexpr auto operator!=(const Vector2& other) const {
    return !(*this == other);
  }

  template <typename A>
  constexpr auto& operator+=(const A other) {
    x += static_cast<float>(other);
    y += static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator-=(const A other) {
    x -= static_cast<float>(other);
    y -= static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator*=(const A other) {
    x *= static_cast<float>(other);
    y *= static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator/=(const A other) {
    x /= static_cast<float>(other);
    y /= static_cast<float>(other);

    return *this;
  }

  constexpr auto& operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;

    return (*this);
  }

  constexpr auto& operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;

    return (*this);
  }

  template <typename A>
  auto operator+(const A other) const {
    auto buf = Vector2{*this};
    buf += static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator-(const A other) const {
    auto buf = Vector2{*this};
    buf -= static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator*(const A other) const {
    auto buf = Vector2{*this};
    buf *= static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator/(const A other) const {
    auto buf = Vector2{*this};
    buf /= static_cast<float>(other);
    return buf;
  }

  auto operator+(const Vector2& other) const {
    auto buf = *this;

    buf.x += other.x;
    buf.y += other.y;

    return buf;
  }

  auto operator-(const Vector2& other) const {
    auto buf = Vector2{*this};

    buf.x -= other.x;
    buf.y -= other.y;

    return buf;
  }

  auto length() const -> float { return std::sqrt(length_sqr()); }

  constexpr auto length_sqr() const -> float { return x * x + y * y; }

  auto distance(const Vector2& other) const {
    return (other - (*this)).length();
  }

  constexpr auto normalize() { *this /= length(); }

  constexpr auto normalized() const {
    auto vec = Vector2{*this};
    vec.normalize();
    return vec;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << v.x << "\t" << v.y << std::endl;

    return os;
  }
};

class Vector3 {
 public:
  float x, y, z;

  constexpr explicit Vector3(float _x = 0.f, float _y = 0.f, float _z = 0.f)
      : x(_x), y(_y), z(_z) {}

  constexpr explicit Vector3(const float* v) : x(v[0]), y(v[1]), z(v[2]) {}

  constexpr auto empty() const { return x == 0.f && y == 0.f && z == 0.f; }

  constexpr void clear() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
  }

  constexpr auto& operator=(const Vector2& other) {
    x = other.x;
    y = other.y;
    z = 0.f;
    return *this;
  }

  constexpr auto operator==(const Vector3& other) const {
    return (x == other.x && y == other.y && z == other.z);
  }

  constexpr auto operator!=(const Vector3& other) const {
    return !(*this == other);
  }

  template <typename A>
  constexpr auto& operator+=(const A other) {
    x += static_cast<float>(other);
    y += static_cast<float>(other);
    z += static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator-=(const A other) {
    x -= static_cast<float>(other);
    y -= static_cast<float>(other);
    z -= static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator*=(const A other) {
    x *= static_cast<float>(other);
    y *= static_cast<float>(other);
    z *= static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator/=(const A other) {
    x /= static_cast<float>(other);
    y /= static_cast<float>(other);
    z /= static_cast<float>(other);

    return *this;
  }

  constexpr auto& operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;

    return (*this);
  }

  constexpr auto& operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return (*this);
  }

  template <typename A>
  auto operator+(const A other) const {
    auto buf = *this;
    buf += static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator-(const A other) const {
    auto buf = *this;
    buf -= static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator*(const A other) const {
    auto buf = *this;
    buf *= static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator/(const A other) const {
    auto buf = *this;
    buf /= static_cast<float>(other);
    return buf;
  }

  auto operator+(const Vector3& other) const {
    auto buf = *this;

    buf.x += other.x;
    buf.y += other.y;
    buf.z += other.z;

    return buf;
  }

  auto operator-(const Vector3& other) const {
    auto buf = *this;

    buf.x -= other.x;
    buf.y -= other.y;
    buf.z -= other.z;

    return buf;
  }

  auto length_2d() const -> float { return sqrt(length_sqr_2d()); }

  constexpr auto length_sqr_2d() const -> float { return x * x + y * y; }

  auto length() const -> float { return sqrt(length_sqr()); }

  constexpr auto length_sqr() const -> float { return x * x + y * y + z * z; }

  auto distance(const Vector3& other) const -> float {
    return std::abs((other - *this).length());
  }

  auto normalize() -> void {
    *this /= length() + std::numeric_limits<float>::epsilon();
  }

  auto normalized() const {
    auto vec = *this;
    vec.normalize();
    return vec;
  }

  constexpr auto dot(const Vector3& other) const -> float {
    return x * other.x + y * other.y + z * other.z;
  }

  constexpr auto dot(float* other) const -> float {
    return x * other[0] + y * other[1] + z * other[2];
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector3& v) {
    os << v.x << "\t" << v.y << "\t" << v.z << std::endl;

    return os;
  }
};

class Vector4 {
 public:
  float x, y, z, w;

  constexpr explicit Vector4(float _x = 0.f,
                             float _y = 0.f,
                             float _z = 0.f,
                             float _w = 0.f)
      : x(_x), y(_y), z(_z), w(_w) {}

  constexpr explicit Vector4(const float* v)
      : x(v[0]), y(v[1]), z(v[2]), w(v[3]) {}

  constexpr auto empty() const {
    return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
  }

  constexpr void clear() {
    x = 0.f;
    y = 0.f;
    z = 0.f;
    w = 0.f;
  }

  constexpr auto& operator=(const Vector2& other) {
    x = other.x;
    y = other.y;
    z = 0.f;
    w = 0.f;
    return *this;
  }

  constexpr auto& operator=(const Vector3& other) {
    x = other.x;
    y = other.y;
    z = other.z;
    w = 0.f;
    return *this;
  }

  constexpr auto operator==(const Vector4& other) const {
    return (x == other.x && y == other.y && z == other.z && w == other.w);
  }

  constexpr auto operator!=(const Vector4& other) const {
    return !(*this == other);
  }

  template <typename A>
  constexpr auto& operator+=(A other) {
    x += static_cast<float>(other);
    y += static_cast<float>(other);
    z += static_cast<float>(other);
    w += static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator-=(A other) {
    x -= static_cast<float>(other);
    y -= static_cast<float>(other);
    z -= static_cast<float>(other);
    w -= static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator*=(A other) {
    x *= static_cast<float>(other);
    y *= static_cast<float>(other);
    z *= static_cast<float>(other);
    w *= static_cast<float>(other);

    return *this;
  }

  template <typename A>
  constexpr auto& operator/=(A other) {
    x /= static_cast<float>(other);
    y /= static_cast<float>(other);
    z /= static_cast<float>(other);
    w /= static_cast<float>(other);

    return *this;
  }

  constexpr auto& operator+=(const Vector4& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    w += other.w;

    return (*this);
  }

  constexpr auto& operator-=(const Vector4& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    w -= other.w;

    return (*this);
  }

  template <typename A>
  auto operator+(A other) const {
    auto buf = *this;
    buf += static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator-(A other) const {
    auto buf = *this;
    buf -= static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator*(A other) const {
    auto buf = *this;
    buf *= static_cast<float>(other);
    return buf;
  }

  template <typename A>
  auto operator/(A other) const {
    auto buf = *this;
    buf /= static_cast<float>(other);
    return buf;
  }

  auto operator+(const Vector4& other) const {
    auto buf = *this;

    buf.x += other.x;
    buf.y += other.y;
    buf.z += other.z;
    buf.w += other.w;

    return buf;
  }

  auto operator-(const Vector4& other) const {
    auto buf = *this;

    buf.x -= other.x;
    buf.y -= other.y;
    buf.z -= other.z;
    buf.w -= other.w;

    return buf;
  }

  auto length_2d() const -> float { return sqrt(length_sqr_2d()); }

  constexpr auto length_sqr_2d() const -> float { return x * x + y * y; }

  auto length_3d() const -> float { return sqrt(length_sqr_3d()); }

  constexpr auto length_sqr_3d() const -> float {
    return x * x + y * y + z * z;
  }

  auto length() const -> float { return sqrt(length_sqr()); }

  constexpr auto length_sqr() const -> float {
    return x * x + y * y + z * z + w * w;
  }

  auto distance(const Vector4& other) const -> float {
    return (other - (*this)).length();
  }

  auto normalize() -> void { *this /= length(); }

  auto normalized() const {
    auto vec = *this;
    vec.normalize();
    return vec;
  }

  friend std::ostream& operator<<(std::ostream& os, const Vector4& v) {
    os << v.x << "\t" << v.y << "\t" << v.z << "\t" << v.w << std::endl;

    return os;
  }
};
}  // namespace Utils
}  // namespace CodeNamePaste
