#pragma once

namespace MH {
	float constexpr PI{ 3.141593 };
	float abs_(float val);
	float toDeg(float val);
	float toRad(float val);
	float sin_(float angle);
	float asin_(float angle);
	float cos_(float angle);
	float acos_(float angle);
	float tan_(float angle);
	float atan_(float angle);
	float atan2_(float y, float x);
	float clamp(float n, float min, float max);
	float min(float n, float min);
	float max(float n, float max);
	float randRange(float min, float max);
	int randRange(int min, int max);
	float wrapAngleTo180(float angle);
	float wrapAngleTo360(float angle);
	float fade(float t);
	float lerp(float x, float y, float t);

	float len(float x, float y);
	float len3(float x, float y, float z);
}