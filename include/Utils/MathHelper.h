#pragma once
#include "QAngle.h"
#include "Vector.h"

namespace CodeNamePaste {
namespace Utils {
namespace Math {

QAngle VectorAngles(const Vector& forward);

QAngle CalcAngle(const Vector& src, const Vector& dst);
}  // namespace Math
}  // namespace Utils
}  // namespace CodeNamePaste
