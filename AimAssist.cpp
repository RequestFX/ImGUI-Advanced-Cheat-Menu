#include "AimAssist.hpp"
#include "menu/imgui_helper.hpp"
#include "SetManager.hpp"
#include <Windows.h>

AimAssist::AimAssist() : Module(obf("AimAssist"), obf("Helps you at Aiming")) {
	isEnemy = &SetManager::i().add(new Set(true, obf("isEnemy"), getName())).getBVal();
	isMate = &SetManager::i().add(new Set(false, obf("isMate"), getName())).getBVal();
	isBot = &SetManager::i().add(new Set(false, obf("isBot"), getName())).getBVal();
	relativeFOV = &SetManager::i().add(new Set(false, obf("relativeFOV"), getName())).getBVal();
	noSnap = &SetManager::i().add(new Set(false, obf("noSnap"), getName())).getBVal();
	noLock = &SetManager::i().add(new Set(false, obf("noLock"), getName())).getBVal();

	hitbox = &SetManager::i().add(new Set(0, obf("hitbox"), getName())).getIVal();
	targetSelection = &SetManager::i().add(new Set(0, obf("targetSelection"), getName())).getIVal();
	onHold = &SetManager::i().add(new Set(0, obf("onHold"), getName())).getIVal();
	reactionTime = &SetManager::i().add(new Set(200, obf("reactionTime"), getName())).getIVal();
	fov = &SetManager::i().add(new Set(40, obf("fov"), getName())).getIVal();
}