#include <catch.hpp>
#include "Utils/Vector.h"

using namespace CodeNamePaste;
using namespace Utils;

TEST_CASE("Vector can Access Parameters") {
  const Vector3 vec{};
  const Vector3 vec2{1.f, 2.f, 3.f};

  CHECK(vec.x == 0.f);
  CHECK(vec.y == 0.f);
  CHECK(vec.z == 0.f);
  CHECK(vec2.x == 1.f);
  CHECK(vec2.y == 2.f);
  CHECK(vec2.z == 3.f);
}

TEST_CASE("Vector can Access Parameters and modify em") {
  Vector3 vec{};

  CHECK(vec.x == 0.f);
  CHECK(vec.y == 0.f);
  CHECK(vec.z == 0.f);
  vec.x = 1.f;
  vec.y = 2.f;
  vec.z = 3.f;
  CHECK(vec.x == 1.f);
  CHECK(vec.y == 2.f);
  CHECK(vec.z == 3.f);
}

TEST_CASE("Vector can Access Parameters and modify em via x y and z") {
  Vector3 vec{};

  CHECK(vec.x == 0.f);
  CHECK(vec.y == 0.f);
  CHECK(vec.z == 0.f);
  vec.x = 1.f;
  vec.y = 2.f;
  vec.z = 3.f;
  CHECK(vec.x == 1.f);
  CHECK(vec.y == 2.f);
  CHECK(vec.z == 3.f);
}

TEST_CASE("Vector can compare itself") {
  Vector3 vec{};
  Vector3 otherVec{1.f};
  CHECK(vec == vec);
  CHECK_FALSE(vec == otherVec);
  CHECK_FALSE(vec != vec);
  CHECK(vec != otherVec);
}

TEST_CASE("Vector can add stuff") {
  Vector3 vec{};
  Vector3 vec2{1.f, 2.f, 3.f};

  vec += vec2;
  CHECK(vec == vec2);
  vec += vec2;
  CHECK((vec.x == 2.f && vec.y == 4.f && vec.z == 6.f));
  vec = vec + vec;
  CHECK((vec.x == 4.f && vec.y == 8.f && vec.z == 12.f));
}

TEST_CASE("Vector can subtract stuff") {
  Vector3 vec{4.f, 8.f, 12.f};
  Vector3 vec2{2.f, 4.f, 6.f};

  CHECK((vec.x == 4.f && vec.y == 8.f && vec.z == 12.f));
  vec -= vec2;
  CHECK(vec == vec2);
  vec = vec - vec;
  CHECK(vec == Vector3{});
}

TEST_CASE("Vector can calcualte its 2D size") {
  Vector3 myVec{0.f, 0.f, 0.f};
  Vector3 myVec2{10.f, 10.f, -10.f};
  Vector3 myVec3{-10.f, -10.f, 10.f};
  Vector3 myVec4{1337.f, 69.f, 80085.f};
  CHECK(myVec.length_2d() == 0.f);
  CHECK(myVec2.length_2d() == Approx(14.142135623730951f));
  CHECK(myVec3.length_2d() == Approx(14.142135623730951f));
  CHECK(myVec4.length_2d() == Approx(1338.779294730838f));
}
