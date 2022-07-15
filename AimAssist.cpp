#include "AimAssist.hpp"
#include "menu/imgui_helper.hpp"
#include "SetManager.hpp"
#include "menu/imgui_custom.hpp"
#include "menu/Menu.hpp"

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
	reactTime = &SetManager::i().add(new Set(200, 0, 1000, obf("reactionTime"), getName())).getVec3i();
	fov = &SetManager::i().add(new Set(40, 0, 360, obf("fov"), getName())).getVec3i();
}

void AimAssist::renderImGui() {
	ImGui::Checkbox_(obf("Enabled").c_str(), &isToggled());
	ImGui::SameLine();

	int i = *onHold;

	ImGuiHelper::renderCombo(" ", { obf("Toggle"), obf("Hold") }, *onHold, 80);

	ImGui::Hotkey(obf("Hotkey").c_str(), getKey());

	ImGuiHelper::renderCombo(obf("Target Selection"), { obf("By Distance"), obf("By Health") }, *targetSelection, Menu::elementSize);
	std::string targets = "";
	if (*isEnemy || *isMate || *isBot) { // atleast one target
		if (*isEnemy && *isMate && *isBot) targets = obf("All");
		else {
			if (*isEnemy) targets += obf("Enemy,");
			if (*isMate) targets += obf("Mate,");
			if (*isBot) targets += obf("Bots,");
			if (targets.back() == ',') targets.pop_back(); // remove , at the end
		}
	}
	else targets = obf("None");

	ImGui::PushItemWidth(Menu::elementSize);
	if (ImGui::BeginCombo(obf("Targets").c_str(), targets.c_str(), 0)) {
		ImGui::Checkbox_(obf("Enemy").c_str(), isEnemy);
		ImGui::Checkbox_(obf("Mate").c_str(), isMate);
		ImGui::Checkbox_(obf("Bot").c_str(), isBot);
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	ImGuiHelper::renderCombo(obf("Hitbox"), { obf("Head"), obf("Neck"), obf("Body"), obf("Arms"), obf("Hip"), obf("Legs") }, *hitbox, Menu::elementSize);

	ImGui::PushItemWidth(Menu::elementSize);
	ImGui::SliderInt_(obf("Reaction ms").c_str(), &reactTime->x, reactTime->y, reactTime->z);
	ImGui::PopItemWidth();

	ImGui::PushItemWidth(Menu::elementSize);
	ImGui::SliderInt_(obf("FOV").c_str(), &fov->x, fov->y, fov->z);
	ImGui::PopItemWidth();
	ImGui::Checkbox_(obf("Relative FOV").c_str(), relativeFOV);
	ImGui::Checkbox_(obf("No Snap").c_str(), noSnap);
	ImGui::Checkbox_(obf("No Lock").c_str(), noLock);
}