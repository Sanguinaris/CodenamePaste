#define _USE_MATH_DEFINES
#include "Utils/MathHelper.h"

#include <cmath>

using namespace CodeNamePaste;
using namespace Utils;

QAngle Math::VectorAngles(const Vector3& forward) {
  QAngle retAngle{};

  if (forward.y == 0 && forward.x == 0) {
    if (forward.z > 0)
      retAngle.p = 270;
    else
      retAngle.p = 90;
  } else {
    retAngle.p = (atan2f(-forward.z, forward.length_2d()) * -180 /
                        static_cast<float>(M_PI));
    retAngle.y =
        (atan2f(forward.y, forward.x) * 180 / static_cast<float>(M_PI));
    if (retAngle.y < 90)
      retAngle.y += 180;
    else if (retAngle.y == 90)
      retAngle.y = 0;
  }

  return retAngle;
}

QAngle Math::CalcAngle(const Vector3& src, const Vector3& dst) {
  Vector3 delta = src - dst;
  return VectorAngles(delta);
}
