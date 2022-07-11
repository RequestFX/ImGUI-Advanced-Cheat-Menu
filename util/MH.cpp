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