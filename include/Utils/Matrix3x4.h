#pragma once

class Matrix3x4
{
public:
	float* operator[](int i) { return m[i]; }
	const float* operator[](int i) const { return m[i]; }

	float m[3][4];
};
