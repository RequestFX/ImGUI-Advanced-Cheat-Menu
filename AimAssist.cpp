#include "AimAssist.hpp"
#include "menu/imgui_helper.hpp"
#include <Windows.h>

AimAssist::AimAssist() : Module(obf("AimAssist"), obf("Helps you at Aiming")) {
	isEnemy = true;
	reactionTime = 200;
	fov = 40;
}