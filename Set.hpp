#pragma once
#include "util/Vec2H.hpp"
#include "imgui.h"

#include <string>

#define SET_TYPE_BOOL 0
#define SET_TYPE_INT 1
#define SET_TYPE_FLOAT 2
#define SET_TYPE_DOUBLE 3
#define SET_TYPE_SLIDER_I 4
#define SET_TYPE_SLIDER_F 5
#define SET_TYPE_SLIDER_D 6
#define SET_TYPE_VEC4 7

class Set {
	int typeID = -1;
	bool bval;
	int ival;
	float fval;
	double dval;
	ImVec4 vec4;
	Vec3i vec3i;
	Vec3f vec3f;
	Vec3d vec3d;
public:
	std::string ID, ID2;

	Set(bool val, std::string ID, std::string ID2 = ""); // addBool
	Set(int val, std::string ID, std::string ID2 = ""); // addInt
	Set(float val, std::string ID, std::string ID2 = ""); // addFloat
	Set(double val, std::string ID, std::string ID2 = ""); // addDouble

	Set(int val, int min, int max, std::string ID, std::string ID2 = ""); // addISlider
	Set(float val, float min, float max, std::string ID, std::string ID2 = ""); // addFSlider
	Set(double val, double min, double max, std::string ID, std::string ID2 = ""); // addDSlider
	Set(ImVec4 v, std::string ID, std::string ID2 = ""); // addImVec4

	bool& getBVal();
	int& getIVal();
	float& getFVal();
	double& getDVal();
	ImVec4& getVec4();
	Vec3i& getVec3i();
	Vec3f& getVec3f();
	Vec3d& getVec3d();

	void setBVal(bool val);
	void setIVal(int val);
	void setFVal(float val);
	void setDVal(double val);
	void setVec4(ImVec4 v);
	void setVec3i(int val, int min, int max);
	void setVec3f(float val, float min, float max);
	void setVec3d(double val, double min, double max);


	bool isBool();
	bool isInt();
	bool isFloat();
	bool isDouble();
	bool isISlider();
	bool isFSlider();
	bool isDSlider();
	bool isVec4();
};