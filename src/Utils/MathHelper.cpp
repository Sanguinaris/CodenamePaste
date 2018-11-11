#define _USE_MATH_DEFINES
#include "Utils/MathHelper.h"

#include <cmath>

using namespace CodeNamePaste;
using namespace Utils;

QAngle Math::VectorAngles(const Vector& forward) {
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

QAngle Math::CalcAngle(const Vector& src, const Vector& dst) {
  Vector delta = src - dst;
  return VectorAngles(delta);
}
