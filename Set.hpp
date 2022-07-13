#pragma once
#include "util/Singleton.hpp"
#include "imgui.h"

#define SET_ADD_BOOL 0
#define SET_ADD_INT 1
#define SET_ADD_FLOAT 2
#define SET_ADD_DOUBLE 3
#define SET_ADD_SLIDER_I 4
#define SET_ADD_SLIDER_F 5
#define SET_ADD_SLIDER_D 6
#define SET_ADD_VEC4 7

class Set : public Singleton<Set> {
	friend class Singleton<Set>;
	int id = -1, ival, iSliderVal, iSliderMin, iSliderMax;
	bool bval;
	float fval, fSliderVal, fSliderMin, fSliderMax;
	double dval, dSliderVal, dSliderMin, dSliderMax;
	ImVec4 vec4;


public:
	void addBool(bool val);
	void addInt(int val);
	void addFloat(float val);
	void addDouble(float val);

	void addSliderI(int val, int min, int max);
	void addSliderF(float val, float min, float max);
	void addSliderD(double val, double min, double max);
	void addVec4(ImVec4 v);

};