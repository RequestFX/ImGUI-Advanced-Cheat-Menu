#include "RCS.hpp"
#include "menu/imgui_helper.hpp"
#include "SetManager.hpp"
#include <Windows.h>

RCS::RCS() : Module(obf("RCS"), obf("Comprehends for Shooting Recoil")) {
	standalone = &SetManager::i().add(new Set(true, obf("standalone"), getName())).getBVal();

	xPow = &SetManager::i().add(new Set(0.6f, 01.f, 1.f, obf("xPow"), getName())).getVec3f();
	yPow = &SetManager::i().add(new Set(0.5f, 01.f, 1.f, obf("yPow"), getName())).getVec3f();
}