#include "Marker.hpp"
#include "menu/imgui_helper.hpp"
#include "SetManager.hpp"
#include <Windows.h>

Marker::Marker() : Module(obf("Marker"), obf("Render a Marker to Entities Position")) {
	col = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(60, 160, 200, 200), obf("col"), getName())).getVec4();

	renderWhenVisible = &SetManager::i().add(new Set(false, obf("renderWhenVisible"), getName())).getBVal();
	renderBehind = &SetManager::i().add(new Set(true, obf("renderBehind"), getName())).getBVal();
	renderInfront = &SetManager::i().add(new Set(false, obf("renderInfront"), getName())).getBVal();
}