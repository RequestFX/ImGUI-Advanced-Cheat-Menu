#include "Menu.hpp"
#include "Fonts.hpp"
#include "Settings.hpp"
#include <vector>
#include <imgui-SFML.h>
#include <Windows.h>
#include <iostream>

void Menu::setColors() {
	style->Colors[ImGuiCol_WindowBg] = winCol;
	style->Colors[ImGuiCol_Border] = ImColor(0, 0, 0, 0);
	style->Colors[ImGuiCol_Button] = bgCol;
	style->Colors[ImGuiCol_ButtonActive] = btnActiveCol;
	style->Colors[ImGuiCol_ButtonHovered] = btnHoverCol;
	style->Colors[ImGuiCol_FrameBg] = bgCol;
	style->Colors[ImGuiCol_FrameBgActive] = frameCol;
	style->Colors[ImGuiCol_FrameBgHovered] = hoverCol;
	style->Colors[ImGuiCol_Text] = textCol;
	style->Colors[ImGuiCol_ChildBg] = childCol;
	style->Colors[ImGuiCol_CheckMark] = itemActiveCol;
	style->Colors[ImGuiCol_SliderGrab] = itemCol;
	style->Colors[ImGuiCol_SliderGrabActive] = itemActiveCol;
	style->Colors[ImGuiCol_Header] = itemActiveCol;
	style->Colors[ImGuiCol_HeaderHovered] = itemCol;
	style->Colors[ImGuiCol_HeaderActive] = itemActiveCol;
	style->Colors[ImGuiCol_ResizeGrip] = resizeGripCol;
	style->Colors[ImGuiCol_ResizeGripHovered] = resizeGripHoverCol;
	style->Colors[ImGuiCol_ResizeGripActive] = itemActiveCol;
	style->Colors[ImGuiCol_SeparatorHovered] = resizeGripHoverCol;
	style->Colors[ImGuiCol_SeparatorActive] = itemActiveCol;
	style->Colors[ImGuiCol_TitleBgActive] = itemActiveCol;
}

void Menu::loadFont() {
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	io.Fonts->Clear(); // clear fonts if you loaded some before (even if only default one was loaded)

	ImFontConfig font_cfg;
	font_cfg.FontDataOwnedByAtlas = false; // if true it will try to free memory and fail
	io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 18, &font_cfg);

	static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
	ImFontConfig icons_config;
	icons_config.MergeMode = true;
	icons_config.PixelSnapH = true;
	icons_config.FontDataOwnedByAtlas = false;
	io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 18, &icons_config, icons_ranges);

	ImFontConfig bigFontCfg;
	bigFontCfg.FontDataOwnedByAtlas = false; // if true it will try to free memory and fail
	bigFont = io.Fonts->AddFontFromMemoryTTF((void*)poppinsFont, sizeof(poppinsFont), 24, &bigFontCfg);
	io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome, sizeof(fontAwesome), 18, &icons_config, icons_ranges);

	ImGui::SFML::UpdateFontTexture(); // important call: updates font texture
}

void Menu::loadTheme() {
	loadFont();

	logoTx = new sf::Texture();
	//logoTx->setSmooth(true);
	logoTx->loadFromMemory((void*)logo, sizeof(logo));


	style = &ImGui::GetStyle();

	// ROUNDINGS
	style->WindowRounding = 6;
	style->ChildRounding = 6;
	style->FrameRounding = 2;
	style->GrabRounding = 2;
	style->PopupRounding = 2; // Combobox

	style->ScrollbarSize = 9;
	style->FramePadding = ImVec2(6, 3);
	style->ItemSpacing = ImVec2(4, 4);

	setColors();
}

ImVec4 rgbaToVec4(float r, float g, float b, float a) {
	return ImVec4(r / 255.0, g / 255.0, b / 255.0, a / 255.0);
}

void Menu::renderLogo() {
	ImGui::BeginGroup(); { // group it so we can redirect to Website when its pressed
		ImGui::BeginChild("Logo", ImVec2(158, 50), true);

		sf::Sprite sprite(*logoTx);
		ImGui::Image(sprite);

		ImGui::PushFont(bigFont);
		ImGui::SameLine();

		ImGui::SetCursorPosY(11); // dont know how to center it sorry :>
		ImGui::TextUnformatted("Big Paste");
		ImGui::PopFont();

		ImGui::EndChild();

		if (ImGui::IsItemClicked(1)) { // redirect to a website/discord on right click
			::ShellExecuteA(NULL, "open", "https://www.youtube.com/watch?v=dQw4w9WgXcQ", NULL, NULL, SW_SHOWDEFAULT);
		}

		ImGui::EndGroup();
	}
}

void Menu::renderUser() {

	int height = 80;
	ImGui::Dummy(ImVec2(0.0f, ImGui::GetContentRegionAvail().y - height - style->ItemSpacing.y));
	ImGui::BeginChild("User", ImVec2(158, height), true);

	ImGui::EndChild();
}

void Menu::renderPanel() {
	renderLogo();
	ImGui::Spacing();
	renderTabs();
	renderUser();
}

void Menu::renderTabs() {
	ImGui::BeginChild("tabs", ImVec2(158, 220), true);

	ImGuiTextFilter2 filter;
	filter.Draw2(ICON_FA_SEARCH" Search", 140);
	ImGui::Spacing();

	ImVec4 col(0, 0, 0, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10); // round buttons
	std::string tabNames[] = { ICON_FA_CROSSHAIRS " LegitBot", ICON_FA_EYE " Visuals", ICON_FA_COG " Misc", ICON_FA_SAVE " Configs" };
	for (int i = 0; i < sizeof(tabNames) / sizeof(tabNames[0]); i++) {
		std::string it = tabNames[i];
		ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, ImVec2(0, 0.5));
		ImGui::PushStyleColor(ImGuiCol_Button, selectedTab == i ? style->Colors[ImGuiCol_ButtonActive] : col);
		ImGui::PushStyleColor(ImGuiCol_Text, selectedTab == i ? style->Colors[ImGuiCol_Text] : notSelectedTextColor);
		if (ImGui::Button(it.c_str(), ImVec2(140, 40))) selectedTab = i;
		ImGui::PopStyleVar();
		ImGui::PopStyleColor(2);
	}
	ImGui::PopStyleVar();

	ImGui::EndChild();
}

void renderCombo(const char* title, const char* items[], int itemSize, int& index, int comboWidth) {
	ImGui::PushItemWidth(comboWidth);
	if (ImGui::BeginCombo(title, items[index], 0)) {

		for (int n = 0; n < itemSize; n++) {
			const bool is_selected = (index == n);
			if (ImGui::Selectable(items[n], is_selected))index = n;

			if (is_selected)ImGui::SetItemDefaultFocus();// Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth();
}

void Menu::renderSubTab0() {
	std::vector<std::string> arr = { "AimAssist", "TriggerBot", "Other" };
	ImGuiHelper::drawTabHorizontally("subtab-0", ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab0);
	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild("modules-wrapper", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab0) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild("aimassist", ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::Checkbox_("Enabled", &isAimAssistEnabled);
		ImGui::SameLine();

		const char* items[] = { "Toggle", "Hold" };
		renderCombo(" ", items, sizeof(items) / sizeof(items[0]), aimAssistOnHold, 80);

		ImGui::Hotkey("Hotkey", aimAssistKey);

		const char* items1[] = { "By Distance", "By Health" };
		renderCombo("Target Selection", items1, sizeof(items1) / sizeof(items1[0]), aimTargetSelection, elementSize);
		std::string targets = "";
		if (!isAimEnemyTarget && !isAimMateTarget && !isAimBotTarget) targets = "None";
		else {
			if (isAimEnemyTarget) targets += " E";
			if (isAimMateTarget) targets += " M";
			if (isAimBotTarget) targets += " B";
		}
		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo("Targets", targets.c_str(), 0)) {
			ImGui::Checkbox_("Enemy", &isAimEnemyTarget);
			ImGui::Checkbox_("Mate", &isAimMateTarget);
			ImGui::Checkbox_("Bot", &isAimBotTarget);
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		const char* items2[] = { "Head", "Neck", "Body", "Arms", "Hip", "Legs" };
		renderCombo("Hitbox", items2, sizeof(items2) / sizeof(items2[0]), aimHitbox, elementSize);

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderInt_2("Reaction ms", &reactionms, 0, 1000);
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderInt_2("FOV", &fov, 0, 180);
		ImGui::PopItemWidth();
		ImGui::Checkbox_("Relative FOV", &relativeFOV);
		ImGui::Checkbox_("No Snap", &noAimSnap);
		ImGui::Checkbox_("No Lock", &noAimLock);
		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild("aimassist2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::Checkbox_("Enable Recoil Control", &isRCS);
		ImGui::Checkbox_("Standalone", &standaloneRCS);

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderFloat_("X Strength", &rcsXStrength, 0.1, 1);
		ImGui::SliderFloat_("Y Strength", &rcsYStrength, 0.1, 1);
		ImGui::PopItemWidth();

		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild("aimassist3", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();

		break;
	}
	case 1: {

		break;
	}
	case 2: {

		break;
	}
	}

	ImGui::EndChild();
}

void Menu::renderSubTab1() {
	std::vector<std::string> arr = { "ESP", "World", "Other" };
	ImGuiHelper::drawTabHorizontally("subtab-1", ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab1);
	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild("modules-wrapper", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab1) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild("esp", ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::Checkbox_("Enabled", &isESPEnabled);

		ImGui::Hotkey("Hotkey", espKey);

		const char* items1[] = { "Enemy", "Mate", "Bot" };
		renderCombo("Type", items1, sizeof(items1) / sizeof(items1[0]), espType, elementSize);
		ImGui::ColorEdit4("ESP Color##1", (float*)&espCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

		std::string style = "Style";
		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo("Style", style.c_str(), 0)) {
			ImGui::Checkbox_("2D Box", &espShow2D);
			ImGui::Checkbox_("Skeleton", &espShowSkeleton);
			ImGui::Checkbox_("Healthbar", &espShowHealth);
			ImGui::Checkbox_("Head Circle", &espShowHeadCircle);

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::Checkbox_("Based on Health", &espColByHealth);

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild("Markers", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::Checkbox_("Enable Markers", &isESPMarkers);
		ImGui::ColorEdit4("Marker Color##1", (float*)&markerCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild("esp2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();

		break;
	}
	case 1: {

		break;
	}
	case 2: {

		break;
	}
	}

	ImGui::EndChild();
}

void Menu::renderSubTab2() {
	std::vector<std::string> arr = { "General", "Other" };
	ImGuiHelper::drawTabHorizontally("subtab-2", ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab2);

	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild("modules-wrapper", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab2) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild("misc##0-0", ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::Checkbox_("Show Module List", &isModuleList);
		ImGui::ColorEdit4("Background Color##1", (float*)&moduleListBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		const char* items1[] = { "ASC", "DSC" };
		renderCombo("Sort", items1, sizeof(items1) / sizeof(items1[0]), moduleListSortby, elementSize);

		const char* items2[] = { "Left", "Right", "Middle" };
		renderCombo("Align", items2, sizeof(items2) / sizeof(items2[0]), moduleListAlign, elementSize);

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild("misc##0-1", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild("misc##0-2", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();
		break;
	}
	case 1: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild("gui", ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::ColorEdit4("Window Color##1", (float*)&winCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("BackGround Color##1", (float*)&childCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("Frame Color##1", (float*)&frameCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("Button Color##1", (float*)&bgCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("Button Hovered Color##1", (float*)&btnHoverCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("Button Active Color##1", (float*)&btnActiveCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("Item Color##1", (float*)&itemCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4("Item Active Color##1", (float*)&itemActiveCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

		setColors(); // not optimal to call all at once but this should be no problem to handle

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild("smth", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild("whoknows", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();
		break;
	}
	}

	ImGui::EndChild();
}

void Menu::renderSubTab3() {
	ImGui::BeginChild("config-tab", ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);

	ImGui::EndChild();
}

void Menu::render() {
	renderModules();

	if (GetAsyncKeyState(VK_INSERT) & 1) { 
		isGUIVisible = !isGUIVisible; }

	if (!isGUIVisible) return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 800,600 });
	ImGui::Begin(" ", 0, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleVar();

	ImGui::Columns(2);
	ImGui::SetColumnOffset(1, 173);

	renderPanel();

	{// Right side
		ImGui::NextColumn();

		switch (selectedTab) {
		case 0: {
			renderSubTab0();
			break;
		}
		case 1: {
			renderSubTab1();
			break;
		}
		case 2: {
			renderSubTab2();
			break;
		}
		case 3: {
			renderSubTab3();// for config, save current(new), load, delete, duplicate, overwrite
			break;
		}
		}
	}
	ImGui::End();
}

void Menu::renderModules() {
	if (!isModuleList) return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 120.f,200.f });
	ImGui::PushStyleColor(ImGuiCol_WindowBg, moduleListBg);
	ImGui::Begin("  ", 0, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleVar();
	ImGui::PopStyleColor();

	{ // best if you have these in an array and sort them by length
		if (isRCS)
			ImGui::Text("Recoil Control");
		if (isAimAssistEnabled)
			ImGui::Text("AimAssist");
		if (isESPEnabled)
			ImGui::Text("ESP");
	}

	ImGui::End();
}