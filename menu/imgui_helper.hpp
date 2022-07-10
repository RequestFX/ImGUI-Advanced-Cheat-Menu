#pragma once
#include <imgui.h>

#include <vector>
#include <string>

namespace ImGuiHelper {
	void drawTabHorizontally(std::string childName, ImVec2 childSize, std::vector<std::string>tabNames, int& selectedSubTab); // draws togglebuttons(tabs) in a child
	float getWidth();
	float getHeight();
	ImVec4 rgbaToVec4(float r, float g, float b, float a);
	ImVec4 rgbaToVec4(ImColor& col);
	ImVec2 getTextLength(std::string text);
}