#include "ESP.hpp"
#include "menu/imgui_helper.hpp"
#include "menu/imgui_custom.hpp"
#include "menu/Menu.hpp"
#include "SetManager.hpp"
#include <Windows.h>

ESP::ESP() : Module(obf("ESP"), obf("Render Entities through Walls"), VK_DIVIDE) {
	colSkeleton = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(222, 144, 154, 200), obf("colSkeleton"), getName())).getVec4();
	col2DBox = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(114, 222, 154, 200), obf("col2DBox"), getName())).getVec4();
	colHealthBar = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(114, 144, 222, 200), obf("colHealthBar"), getName())).getVec4();
	colHeadCircle = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(188, 169, 154, 200), obf("colHeadCircle"), getName())).getVec4();

	isSkeleton = &SetManager::i().add(new Set(false, obf("isSkeleton"), getName())).getBVal();
	is2DBox = &SetManager::i().add(new Set(false, obf("is2DBox"), getName())).getBVal();
	isHealthBar = &SetManager::i().add(new Set(false, obf("isHealthBar"), getName())).getBVal();
	isHeadCircle = &SetManager::i().add(new Set(false, obf("isHeadCircle"), getName())).getBVal();
	isEnemy = &SetManager::i().add(new Set(true, obf("isEnemy"), getName())).getBVal();
	isMate = &SetManager::i().add(new Set(false, obf("isMate"), getName())).getBVal();
	isBot = &SetManager::i().add(new Set(false, obf("isBot"), getName())).getBVal();
	isSkeletonHealthBased = &SetManager::i().add(new Set(false, obf("isSkeletonHealthBased"), getName())).getBVal();
	is2DBoxHealthBased = &SetManager::i().add(new Set(false, obf("is2DBoxHealthBased"), getName())).getBVal();
	isHealthBarHealthBased = &SetManager::i().add(new Set(false, obf("isHealthBarHealthBased"), getName())).getBVal();
	isHeadCircleHealthBased = &SetManager::i().add(new Set(false, obf("isHeadCircleHealthBased"), getName())).getBVal();
}

void ESP::renderImGui() {
	ImGui::Checkbox_(obf("Enabled").c_str(), &isToggled());

	ImGui::Hotkey(obf("Hotkey").c_str(), getKey());

	ImGui::PushItemWidth(Menu::elementSize);
	if (ImGui::BeginCombo(obf("Type").c_str(), obf("Type").c_str(), 0)) {
		ImGui::Checkbox_(obf("Enemy").c_str(), isEnemy);
		ImGui::Checkbox_(obf("Mate").c_str(), isMate);
		ImGui::Checkbox_(obf("Bot").c_str(), isBot);

		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();

	ImGui::PushItemWidth(Menu::elementSize);
	if (ImGui::BeginCombo(obf("2D Box Style").c_str(), obf("Style").c_str(), 0)) {
		ImGui::Checkbox_(obf("2D Box").c_str(), is2DBox);
		ImGui::ColorEdit4(obf("2D Box Color##1").c_str(), (float*)col2DBox, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::Checkbox_(obf("2D Box Based on Health").c_str(), is2DBoxHealthBased);
		ImGui::EndCombo();
	}
	if (ImGui::BeginCombo(obf("Skeleton Style").c_str(), obf("Style").c_str(), 0)) {
		ImGui::Checkbox_(obf("Skeleton").c_str(), isSkeleton);
		ImGui::ColorEdit4(obf("Skeleton Color##1").c_str(), (float*)colSkeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::Checkbox_(obf("Skeleton Based on Health").c_str(), isSkeletonHealthBased);
		ImGui::EndCombo();
	}
	if (ImGui::BeginCombo(obf("Healthbar Style").c_str(), obf("Style").c_str(), 0)) {
		ImGui::Checkbox_(obf("Healthbar").c_str(), isHealthBar);
		ImGui::ColorEdit4(obf("Healthbar Color##1").c_str(), (float*)&colHealthBar, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::Checkbox_(obf("Healthbar Based on Health").c_str(), isHealthBarHealthBased);
		ImGui::EndCombo();
	}
	if (ImGui::BeginCombo(obf("Head Circle Style").c_str(), obf("Style").c_str(), 0)) {
		ImGui::Checkbox_(obf("Head Circle").c_str(), isHeadCircle);
		ImGui::ColorEdit4(obf("Head Circle Color##1").c_str(), (float*)colHeadCircle, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::Checkbox_(obf("Head Circle Based on Health").c_str(), isHeadCircleHealthBased);
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
}