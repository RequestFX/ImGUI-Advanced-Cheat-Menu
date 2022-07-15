#pragma once

#include "../util/Obf.hpp"
#include "imgui_custom.hpp"
#include "../SetManager.hpp"

#include <string>
#include <SFML/Graphics.hpp>

namespace Menu {
	inline ImVec4* winCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(0, 0, 0, 230), obf("winCol"))).getVec4(),
		* bgCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(31, 30, 31, 255), obf("bgCol"))).getVec4(),
		* childCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(33, 34, 45, 255), obf("childCol"))).getVec4(),
		* childCol1 = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(38, 39, 50, 255), obf("childCol1"))).getVec4(),
		* notSelectedTextColor = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(140, 140, 140, 255), obf("notSelectedTextColor"))).getVec4(),
		* textCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(255, 255, 255, 255), obf("textCol"))).getVec4(),
		* btnActiveCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(239, 73, 88, 255), obf("btnActiveCol"))).getVec4(),
		* btnHoverCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(173, 55, 65, 255), obf("btnHoverCol"))).getVec4(),

		* frameCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(44, 43, 44, 255), obf("frameCol"))).getVec4(),
		* hoverCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(37, 36, 37, 255), obf("hoverCol"))).getVec4(),
		* itemCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(240, 74, 88, 255), obf("hoverCol"))).getVec4(),
		* itemActiveCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(240, 50, 66, 255), obf("hoverCol"))).getVec4(),
		* resizeGripCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(220, 50, 66, 120), obf("hoverCol"))).getVec4(),
		* resizeGripHoverCol = &SetManager::i().add(new Set(ImGuiHelper::rgbaToVec4(250, 50, 66, 140), obf("hoverCol"))).getVec4();

	inline bool isGUIVisible = true;

	inline ImGuiStyle* style;
	inline int selectedTab = 0, selectedSubTab0 = 0, selectedSubTab1 = 0, selectedSubTab2 = 0, elementSize = 120;

	inline sf::Texture* logoTx;
	inline ImFont* bigFont;

	void setColors();

	void loadFont();
	void loadTheme();

	void renderPanel(); // left panel
	void renderLogo();
	void renderUser();
	void renderTabs();
	void renderSubTab0();
	void renderSubTab1();
	void renderSubTab2();

	void render();

}