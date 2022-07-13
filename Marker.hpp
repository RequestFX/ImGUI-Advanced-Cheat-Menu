#pragma once
#include "imgui.h"
#include "util/Obf.hpp"
#include "util/Singleton.hpp"
#include "Module.hpp"

class Marker : public Singleton<Marker>, public Module {
	friend class Singleton<Marker>;
public:
	ImVec4 col;
	bool renderWhenVisible; // always render, only when visible, only when not visible, 
	bool renderBehind, renderInfront;

	Marker();

	void onEnable() override {}
	void onDisable() override {}
};