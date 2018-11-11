#include <catch.hpp>

#include "Utils/MathHelper.h"

using namespace CodeNamePaste;
using namespace Utils;

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
