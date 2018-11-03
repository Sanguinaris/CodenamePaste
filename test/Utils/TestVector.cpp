#include <catch.hpp>
#include "Utils/Vector.h"

using namespace CodeNamePaste;
using namespace Utils;

float* GimmeAVec() {
  float* fl = new float[3];
  fl[0] = 1.f;
  fl[1] = 1.f;
  fl[2] = 1.f;
  return fl;
}

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

TEST_CASE("Can Access Parameters and modify em via x y and z") {
  Vector vec{};

  CHECK(vec.x == 0.f);
  CHECK(vec.y == 0.f);
  CHECK(vec.z == 0.f);
  vec.x.get() = 1.f;
  vec.y.get() = 2.f;
  vec.z.get() = 3.f;
  CHECK(vec.x == 1.f);
  CHECK(vec.y == 2.f);
  CHECK(vec.z == 3.f);
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

TEST_CASE("Vector works with External Vector") {
  Vector myVec = GimmeAVec();

  CHECK(myVec.x == Approx(1.f));
  CHECK(myVec.y == Approx(1.f));
  CHECK(myVec.z == Approx(1.f));
}
