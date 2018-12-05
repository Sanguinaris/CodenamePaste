#pragma once
#include "QAngle.h"
#include "Vector.h"

namespace CodeNamePaste {
namespace Utils {
namespace Math {

QAngle VectorAngles(const Vector3& forward);

QAngle CalcAngle(const Vector3& src, const Vector3& dst);
}  // namespace Math
}  // namespace Utils
}  // namespace CodeNamePaste
