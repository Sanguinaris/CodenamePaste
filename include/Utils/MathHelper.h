#pragma once
#include "Vector.h"
#include "QAngle.h"

namespace CodeNamePaste{
namespace Utils{
    namespace Math {

QAngle VectorAngles(const Vector& forward);

QAngle CalcAngle(const Vector& src, const Vector& dst);
}  // namespace Math
}
}
