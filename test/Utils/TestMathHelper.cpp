#define _USE_MATH_DEFINES

#include <catch.hpp>

#include <cmath>
#include "Utils/QAngle.h"
#include "Utils/Vector.h"

using namespace CodeNamePaste;
using namespace Utils;

namespace Math {

QAngle VectorAngles(const Vector& forward) {
  QAngle retAngle{};

  if (forward.y == 0 && forward.x == 0) {
    if (forward.z > 0)
      retAngle.x.get() = 270;
    else
      retAngle.x.get() = 90;
  } else {
    retAngle.x.get() = (atan2f(-forward.z, forward.Length2D()) * -180 / M_PI);
    retAngle.y.get() = (atan2f(forward.y, forward.x) * 180 / M_PI);
    if (retAngle.y < 90)
      retAngle.y += 180;
    else if (retAngle.y == 90)
      retAngle.y.get() = 0;
  }

  return retAngle;
}

QAngle CalcAngle(const Vector& src, const Vector& dst) {
  Vector delta = src - dst;
  return VectorAngles(delta);
}
}  // namespace Math

TEST_CASE(
    "MathHelper is capable of Calculating an Angle between two positions") {
  GIVEN("Two Vector Positions") {
    Vector source{100.f, 200.f, -150.f};
    Vector destination{-100.f, 0.f, 350.f};

    WHEN("Calculating the angles") {
      auto dstAngle = Math::CalcAngle(source, destination);
      THEN("They should match") {
        CHECK(dstAngle.x == Approx(-60.5038f));
        CHECK(dstAngle.y == Approx(225.f));
        CHECK(dstAngle[2] == 0.f);
      }
    }
  }
  GIVEN("Two Vector Positions") {
    Vector source{0, 0, 0};
    Vector destination{0, 0, 0};

    WHEN("Calculating the angles") {
      auto dstAngle = Math::CalcAngle(source, destination);
      THEN("They should match") {
        CHECK(dstAngle.x == 90);
        CHECK(dstAngle.y == 0);
        CHECK(dstAngle[2] == 0.f);
      }
    }
  }
  GIVEN("Two Vector Positions") {
    Vector source{0, 0, 10};
    Vector destination{0, 0, 0};

    WHEN("Calculating the angles") {
      auto dstAngle = Math::CalcAngle(source, destination);
      THEN("They should match") {
        CHECK(dstAngle.x == 270);
        CHECK(dstAngle.y == 0);
        CHECK(dstAngle[2] == 0.f);
      }
    }
  }
  GIVEN("Two Vector Positions") {
    Vector source{9999999, 0, -99};
    Vector destination{0, 9999999, 0};

    WHEN("Calculating the angles") {
      auto dstAngle = Math::CalcAngle(source, destination);
      THEN("They should match") {
        CHECK(dstAngle.x == Approx(-0.000401091f));
        CHECK(dstAngle.y == 135);
        CHECK(dstAngle[2] == 0.f);
      }
    }
  }
  GIVEN("Two Vector Positions") {
    Vector source{0, 1, -99};
    Vector destination{0, 0, 0};

    WHEN("Calculating the angles") {
      auto dstAngle = Math::CalcAngle(source, destination);
      THEN("They should match") {
        CHECK(dstAngle.x == Approx(-89.4213f));
        CHECK(dstAngle.y == 0);
        CHECK(dstAngle[2] == 0.f);
      }
    }
  }
}
