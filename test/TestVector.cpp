#include <catch.hpp>
#include "Utils/Vector.h"

TEST_CASE("Can Access Parameters") {
  const Vector vec{};
  const Vector vec2{1.f, 2.f, 3.f};

  CHECK(vec[0] == 0.f);
  CHECK(vec[1] == 0.f);
  CHECK(vec[2] == 0.f);
  CHECK(vec2[0] == 1.f);
  CHECK(vec2[1] == 2.f);
  CHECK(vec2[2] == 3.f);
}

TEST_CASE("Can Access Parameters and modify em") {
  Vector vec{};

  CHECK(vec[0] == 0.f);
  CHECK(vec[1] == 0.f);
  CHECK(vec[2] == 0.f);
  vec[0] = 1.f;
  vec[1] = 2.f;
  vec[2] = 3.f;
  CHECK(vec[0] == 1.f);
  CHECK(vec[1] == 2.f);
  CHECK(vec[2] == 3.f);
}

TEST_CASE("Vector can compare itself") {
  Vector vec{};
  Vector otherVec{1.f};
  CHECK(vec == vec);
  CHECK_FALSE(vec == otherVec);
  CHECK_FALSE(vec != vec);
  CHECK(vec != otherVec);
}

TEST_CASE("Vector can add stuff") {
  Vector vec{};
  Vector vec2{1.f, 2.f, 3.f};

  vec += vec2;
  CHECK(vec == vec2);
  vec += vec2;
  CHECK((vec.x == 2.f && vec.y == 4.f && vec.z == 6.f));
  vec = vec + vec;
  CHECK((vec.x == 4.f && vec.y == 8.f && vec.z == 12.f));
}

TEST_CASE("Vector can subtract stuff") {
  Vector vec{4.f, 8.f, 12.f};
  Vector vec2{2.f, 4.f, 6.f};

  CHECK((vec.x == 4.f && vec.y == 8.f && vec.z == 12.f));
  vec -= vec2;
  CHECK(vec == vec2);
  vec = vec - vec;
  CHECK(vec == Vector{});
}
