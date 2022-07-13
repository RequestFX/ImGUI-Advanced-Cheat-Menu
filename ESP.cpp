#include "ESP.hpp"
#include "menu/imgui_helper.hpp"
#include <Windows.h>

ESP::ESP() : Module(obf("ESP"), obf("Render Entities through Walls"), VK_DIVIDE) {
	colSkeleton = ImGuiHelper::rgbaToVec4(222, 144, 154, 200);
	col2DBox = ImGuiHelper::rgbaToVec4(114, 222, 154, 200);
	colHealthBar = ImGuiHelper::rgbaToVec4(114, 144, 222, 200);
	colHeadCircle = ImGuiHelper::rgbaToVec4(188, 169, 154, 200);

	isEnemy = true;
}