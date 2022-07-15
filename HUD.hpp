#pragma once
#include "imgui.h"
#include "util/Obf.hpp"
#include "util/Singleton.hpp"
#include "Module.hpp"

class HUD : public Singleton<HUD>, public Module {
	friend class Singleton<HUD>;
public:
	int* alignML, * sortML;
	ImVec4* colML, * colML_Bg;
	Vec3f* speedML, *offsetML, *rangeML;
	bool* isML, * isMLRainbow, // render Module List
		* isTime;

	HUD();
	void render();
	void renderML();

	void onEnable() override {}
	void onDisable() override {}
};