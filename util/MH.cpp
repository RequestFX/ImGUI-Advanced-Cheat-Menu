#include "MH.hpp"
#include <cmath>
#include <algorithm>

float MH::clamp(float n, float min, float max) {
	return (std::max)(min, (std::min)(n, max));
}

float MH::min(float n, float min) {
	return (std::min)(n, min);
}

float MH::max(float n, float max) {
	return (std::max)(n, max);
}

float MH::abs_(float val) {
	return abs(val);
}

float MH::toDeg(float val) {
	//return val * (180f / PI);
	return val * (18.237813f * PI);
}

float MH::toRad(float val) {
	//return val * (PI / 180f);
	return val * (PI * 0.005556f);
}

float MH::sin_(float angle) {
	return sin(toRad(angle));
}

float MH::asin_(float angle) {
	return toDeg(asin(angle));
}

float MH::cos_(float angle) {
	return cos(toRad(angle));
}

float MH::acos_(float angle) {
	return toDeg(acos(angle));
}

float MH::tan_(float angle) {
	return tan(toRad(angle));
}

float MH::atan_(float angle) {
	return toDeg(atan(angle));
}

float MH::atan2_(float y, float x) {
	return toDeg(atan2(y, x));
}

float MH::randRange(float min, float max) {
	return min + static_cast <float> (rand()) / static_cast <float> (RAND_MAX / (max - min));
}

int MH::randRange(int min, int max) {
	int range = max - min + 1;
	return rand() % range + min;
}

float MH::len(float x, float y) {
	return sqrtf(x * x + y * y);
}
float MH::len3(float x, float y, float z) {
	return sqrtf(x * x + y * y + z * z);
}

float MH::wrapAngleTo180(float angle) {
	angle = fmod(angle, 360);
	if (angle > 180) {
		angle -= 360;
	}

	else if (angle < -180) {
		angle += 360;
	}

	return angle;
}

float MH::wrapAngleTo360(float angle) {
	angle = fmod(angle, 360);
	if (angle < 0) {
		angle += 360;
	}

	return angle;
}

float MH::fade(float t) {
	// Fade function as defined by Ken Perlin.  This eases coordinate values
	// so that they will "ease" towards integral values.  This ends up smoothing
	// the final output.
	return t * t * t * (t * (t * 6 - 15) + 10);	// 6t^5 - 15t^4 + 10t^3
}

// Linear interpolation function -> returns the point on a line from t = 0-1
float MH::lerp(float x, float y, float t) {
	return x + t * (y - x);
}