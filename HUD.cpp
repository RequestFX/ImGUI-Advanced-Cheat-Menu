#include "HUD.hpp"
#include "util/ColorH.hpp"
#include "menu/imgui_helper.hpp"
#include "menu/imgui_custom.hpp"
#include "ModuleManager.hpp"
#include "util/TimeH.hpp"
#include "SetManager.hpp"

#include <Windows.h>

HUD::HUD() : Module(obf("HUD"), obf("Renders Overlay like ModuleList")) {
	colML = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(255, 100, 100, 255), obf("colML"), getName())).getVec4();
	colML_Bg = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(0, 0, 0, 100), obf("colML_Bg"), getName())).getVec4();

	speedML = &SetManager::i().add(new Set(0.4f, 0.1f, 1.f, obf("speedML"), getName())).getVec3f();
	offsetML = &SetManager::i().add(new Set(0.06f, 0.f, 0.4f, obf("offsetML"), getName())).getVec3f();
	rangeML = &SetManager::i().add(new Set(0.02f, 0.f, 0.1f, obf("rangeML"), getName())).getVec3f();

	isML = &SetManager::i().add(new Set(false, obf("isML"), getName())).getBVal();
	isMLRainbow = &SetManager::i().add(new Set(true, obf("isMLRainbow"), getName())).getBVal();
	isTime = &SetManager::i().add(new Set(false, obf("isTime"), getName())).getBVal();

	alignML = &SetManager::i().add(new Set(0, obf("alignML"), getName())).getIVal();
	sortML = &SetManager::i().add(new Set(1, obf("sortML"), getName())).getIVal();
}

void HUD::renderML() {
	if (!*isML) return;

	ImVec2 winPadding = ImGui::GetStyle().WindowPadding;
	std::vector<std::string*>modules;
	float calcHeight = winPadding.y * 2, longestStr = 0, shortestStr;

	for (int i = 0; i < ModuleManager::i().modules.size(); i++) {
		Module* m = ModuleManager::i().modules.at(i);
		if (!m->isToggled()) continue;

		ImVec2 vec2 = ImGui::CalcTextSize(m->getName().c_str());
		if (vec2.x > longestStr) longestStr = vec2.x;
		calcHeight += vec2.y;

		modules.push_back(&m->getName());
	}
	if (modules.size() == 0) return; // no Module active

	calcHeight += ImGui::GetStyle().ItemSpacing.y * (modules.size() - 1); // itemspacing;

	ImGui::SetNextWindowSize({ longestStr + winPadding.x * 2, calcHeight });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, *colML_Bg);
	ImGui::Begin("  ", 0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleColor();

	if (sortML == 0) {

	}

	if (*isMLRainbow) {
		for (int i = 0; i < modules.size(); i++) {
			std::string* str = modules.at(i);
			float h, s, v;
			ColorH::RGBtoHSV(colML->x, colML->y, colML->z, h, s, v);

			if ((*alignML == 1 || *alignML == 2) && i != 0) {
				float width = ImGui::CalcTextSize(str->c_str()).x;
				if (*alignML == 1) ImGui::Dummy(ImVec2(longestStr - width - ImGui::GetStyle().ItemSpacing.x, 0));
				else ImGui::Dummy(ImVec2((longestStr - width) * 0.5 - ImGui::GetStyle().ItemSpacing.x, 0));
				ImGui::SameLine();
			}
			ImGui::chromaText(*str, s, v, colML->w, i * (offsetML->x + 1), speedML->x, rangeML->x);
		}
	}
	else {
		for (int i = 0; i < modules.size(); i++) {
			std::string* str = modules.at(i);

			if ((*alignML == 1 || *alignML == 2) && i != 0) {
				float width = ImGui::CalcTextSize(str->c_str()).x;
				if (*alignML == 1) ImGui::Dummy(ImVec2(longestStr - width - ImGui::GetStyle().ItemSpacing.x, 0));
				else ImGui::Dummy(ImVec2((longestStr - width) * 0.5 - ImGui::GetStyle().ItemSpacing.x, 0));
				ImGui::SameLine();
			}

			ImGui::PushStyleColor(ImGuiCol_Text, *colML);
			ImGui::Text(str->c_str());
			ImGui::PopStyleColor();
		}
	}

	ImGui::End();
}

void HUD::render() {
	if (!isToggled()) return;

	renderML();
}