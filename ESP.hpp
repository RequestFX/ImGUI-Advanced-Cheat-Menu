#pragma once
#include "imgui.h"
#include "util/Obf.hpp"
#include "util/Singleton.hpp"
#include "Module.hpp"

class ESP : public Singleton<ESP>, public Module{
	friend class Singleton<ESP>;
public:
	ImVec4 colSkeleton, col2DBox, colHealthBar, colHeadCircle;
	bool isSkeleton, is2DBox, isHealthBar, isHeadCircle, isEnemy, isMate, isBot,
		isSkeletonHealthBased, is2DBoxHealthBased, isHealthBarHealthBased, isHeadCircleHealthBased;

	ESP();

	void onEnable() override {}
	void onDisable() override {}
};