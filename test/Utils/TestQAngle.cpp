#include <catch.hpp>
#include "Utils/QAngle.h"

using namespace CodeNamePaste;
using namespace Utils;

TEST_CASE("QAngle can Access Parameters") {
  const QAngle vec{};
  const QAngle vec2{1.f, 2.f, 3.f};

  CHECK(vec[0] == 0.f);
  CHECK(vec[1] == 0.f);
  CHECK(vec[2] == 0.f);
  CHECK(vec2[0] == 1.f);
  CHECK(vec2[1] == 2.f);
  CHECK(vec2[2] == 3.f);
}

TEST_CASE("QAngle can Access Parameters and modify em") {
  QAngle vec{};

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

TEST_CASE("QAngle can Access Parameters and modify em via x and y") {
  QAngle vec{};

  CHECK(vec.p == 0.f);
  CHECK(vec.y == 0.f);
  CHECK(vec.r == 0.f);
  vec.p = 1.f;
  vec.y = 2.f;
  vec.r = 3.f;
  CHECK(vec.p == 1.f);
  CHECK(vec.y == 2.f);
  CHECK(vec.r == 3.f);
}

TEST_CASE("QAngle can compare itself") {
  QAngle vec{};
  QAngle otherVec{1.f};
  CHECK(vec == vec);
  CHECK_FALSE(vec == otherVec);
  CHECK_FALSE(vec != vec);
  CHECK(vec != otherVec);
}

TEST_CASE("QAngle can add stuff") {
  QAngle vec{};
  QAngle vec2{1.f, 2.f, 3.f};

  vec += vec2;
  CHECK(vec == vec2);
  vec += vec2;
  CHECK((vec.p == 2.f && vec.y == 4.f && vec[2] == 6.f));
  vec = vec + vec;
  CHECK((vec.p == 4.f && vec.y == 8.f && vec[2] == 12.f));
}

TEST_CASE("QAngle can subtract stuff") {
  QAngle vec{4.f, 8.f, 12.f};
  QAngle vec2{2.f, 4.f, 6.f};

  CHECK((vec.p == 4.f && vec.y == 8.f && vec[2] == 12.f));
  vec -= vec2;
  CHECK(vec == vec2);
  vec = vec - vec;
  CHECK(vec == QAngle{});
}
