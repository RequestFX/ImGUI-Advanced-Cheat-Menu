#pragma once
#include "imgui.h"
#include "util/Obf.hpp"
#include "util/Singleton.hpp"
#include "Module.hpp"

class RCS : public Singleton<RCS>, public Module {
	friend class Singleton<RCS>;
public:
	bool* standalone;
	Vec3f* xPow, * yPow;

	RCS();
	void renderImGui();

	void onEnable() override {}
	void onDisable() override {}
};