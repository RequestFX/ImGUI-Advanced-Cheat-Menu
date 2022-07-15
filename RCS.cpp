#include "RCS.hpp"
#include "menu/imgui_helper.hpp"
#include "menu/imgui_custom.hpp"
#include "menu/Menu.hpp"
#include "SetManager.hpp"
#include <Windows.h>

RCS::RCS() : Module(obf("RCS"), obf("Comprehends for Shooting Recoil")) {
	standalone = &SetManager::i().add(new Set(true, obf("standalone"), getName())).getBVal();

	xPow = &SetManager::i().add(new Set(0.6f, 0.1f, 1.f, obf("xPow"), getName())).getVec3f();
	yPow = &SetManager::i().add(new Set(0.5f, 0.1f, 1.f, obf("yPow"), getName())).getVec3f();
}

void RCS::renderImGui() {
	ImGui::Checkbox_(obf("Enable Recoil Control").c_str(), &isToggled());
	ImGui::Checkbox_(obf("Standalone").c_str(), standalone);

	ImGui::PushItemWidth(Menu::elementSize);
	ImGui::SliderFloat_(obf("X Strength").c_str(), &xPow->x, xPow->y, xPow->z);
	ImGui::SliderFloat_(obf("Y Strength").c_str(), &yPow->x, xPow->y, xPow->z);
	ImGui::PopItemWidth();
}