#include "Marker.hpp"
#include "menu/imgui_helper.hpp"
#include <Windows.h>

Marker::Marker() : Module(obf("Marker"), obf("Render a Marker to Entities Position")) {
	col = ImGuiHelper::rgbaToVec4(60, 160, 200, 200);
	renderBehind = true;
}