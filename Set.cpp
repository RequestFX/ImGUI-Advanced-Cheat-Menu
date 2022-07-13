#include "Set.hpp"

void Set::addBool(bool val) {
	bval = val;
	id = SET_ADD_BOOL;
}
void Set::addInt(int val) {
	ival = val;
	id = SET_ADD_INT;
}
void Set::addFloat(float val) {
	fval = val;
	id = SET_ADD_FLOAT;
}
void Set::addDouble(float val) {
	dval = val;
	id = SET_ADD_DOUBLE;
}

void Set::addSliderI(int val, int min, int max) {
	iSliderVal = val;
	iSliderMin = min;
	iSliderMax = max;
	id = SET_ADD_SLIDER_I;
}
void Set::addSliderF(float val, float min, float max) {
	fSliderVal = val;
	fSliderMin = min;
	fSliderMax = max;
	id = SET_ADD_SLIDER_F;
}
void Set::addSliderD(double val, double min, double max) {
	dSliderVal = val;
	dSliderMin = min;
	dSliderMax = max;
	id = SET_ADD_SLIDER_D;
}
void Set::addVec4(ImVec4 v) {
	vec4 = v;
	id = SET_ADD_VEC4;
}