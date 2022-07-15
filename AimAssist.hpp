#pragma once
#include "imgui.h"
#include "util/Obf.hpp"
#include "util/Singleton.hpp"
#include "Module.hpp"

class AimAssist : public Singleton<AimAssist>, public Module {
	friend class Singleton<AimAssist>;
public:
	bool* isEnemy, * isMate, * isBot, * relativeFOV, * noSnap, * noLock;
	int* hitbox, * targetSelection, * onHold, * reactionTime, * fov;

	AimAssist();

	void onEnable() override {}
	void onDisable() override {}
};