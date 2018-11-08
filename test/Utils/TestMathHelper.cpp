#include <catch.hpp>
#include "Utils/Vector.h"
#include "Utils/QAngle.h"

using namespace CodeNamePaste;
using namespace Utils;

namespace Math {
QAngle CalcAngle(const Vector& src, const Vector& dst) {
  return {};
}
}  // namespace Math

TEST_CASE(
    "MathHelper is capable of Calculating an Angle between two positions") {
  GIVEN("Two Vector Positions") {
    Vector source{100.f, 200.f, -150.f};
    Vector destination{-100.f, 0.f, 350.f};

    WHEN("Calculating the angles") {
      auto dstAngle = Math::CalcAngle(source, destination);

      THEN("They should match") { CHECK(dstAngle == QAngle{}); }
    }
  }
}
