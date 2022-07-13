#pragma once

#include "imgui_custom.hpp"
#include <string>
#include <SFML/Graphics.hpp>

namespace Menu {
	static ImVec4 winCol = ImVec4(0, 0, 0, 0.9),
		bgCol = ImVec4(31 / 255.f, 30 / 255.f, 31 / 255.f, 1),
		childCol = ImVec4(33 / 255.f, 34 / 255.f, 45 / 255.f, 1),
		notSelectedTextColor = ImVec4(0.6, 0.6, 0.6, 1),
		textCol = ImVec4(1, 1, 1, 1),
		btnActiveCol = ImVec4(239 / 255.f, 73 / 255.f, 88 / 255.f, 1),
		btnHoverCol = ImVec4(173 / 255.f, 55 / 255.f, 65 / 255.f, 1),

		frameCol = ImVec4(44 / 255.f, 43 / 255.f, 44 / 255.f, 1),
		hoverCol = ImVec4(37 / 255.f, 36 / 255.f, 37 / 255.f, 1),
		itemCol = ImVec4(240 / 255.f, 74 / 255.f, 88 / 255.f, 1),
		itemActiveCol = ImVec4(240 / 255.f, 50 / 255.f, 66 / 255.f, 1),
		resizeGripCol = ImVec4(220 / 255.f, 50 / 255.f, 66 / 255.f, 0.4),
		resizeGripHoverCol = ImVec4(250 / 255.f, 50 / 255.f, 66 / 255.f, 0.6);

	static bool isGUIVisible = true;

	static ImGuiStyle* style;
	static int selectedTab = 0, selectedSubTab0 = 0, selectedSubTab1 = 0, selectedSubTab2 = 0, elementSize = 120;

	static sf::Texture* logoTx;
	static ImFont* bigFont;

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
	void renderSubTab3();

	void render();

}