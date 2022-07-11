#include "Menu.hpp"
#include "../Obf.hpp"
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

void Menu::renderLogo() {
	ImGui::BeginGroup(); { // group it so we can redirect to Website when its pressed
		ImGui::BeginChild(obf("Logo").c_str(), ImVec2(158, 50), true);

		sf::Sprite sprite(*logoTx);
		ImGui::Image(sprite);

		ImGui::PushFont(bigFont);
		ImGui::SameLine();

		ImGui::SetCursorPosY(11); // dont know how to center it sorry :>
		ImGui::TextUnformatted(obf("Big Paste").c_str());
		ImGui::PopFont();

		ImGui::EndChild();

		if (ImGui::IsItemClicked(1)) { // redirect to a website/discord on right click
			::ShellExecuteA(NULL, obf("open").c_str(), obf("https://www.youtube.com/watch?v=dQw4w9WgXcQ").c_str(), NULL, NULL, SW_SHOWDEFAULT);
		}

		ImGui::EndGroup();
	}
}

void Menu::renderUser() {

	int height = 80;
	ImGui::Dummy(ImVec2(0.0f, ImGui::GetContentRegionAvail().y - height - style->ItemSpacing.y));
	ImGui::BeginChild(obf("User").c_str(), ImVec2(158, height), true);

	ImGui::EndChild();
}

void Menu::renderPanel() {
	renderLogo();
	ImGui::Spacing();
	renderTabs();
	renderUser();
}

void Menu::renderTabs() {
	ImGui::BeginChild(obf("tabs").c_str(), ImVec2(158, 220), true);

	ImGuiTextFilter2 filter;
	filter.Draw2(obf(ICON_FA_SEARCH" Search").c_str(), 140);
	ImGui::Spacing();

	ImVec4 col(0, 0, 0, 0);
	ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 10); // round buttons
	std::string tabNames[] = { obf(ICON_FA_CROSSHAIRS " LegitBot"), obf(ICON_FA_EYE " Visuals"), obf(ICON_FA_COG " Misc"), obf(ICON_FA_SAVE " Configs") };
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

void Menu::renderSubTab0() {
	std::vector<std::string> arr = { obf("AimAssist"), obf("TriggerBot"), obf("Other") };
	ImGuiHelper::drawTabHorizontally(obf("subtab-0"), ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab0);
	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild(obf("modules-wrapper").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab0) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild(obf("aimassist").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::Checkbox_(obf("Enabled").c_str(), &isAimAssistEnabled);
		ImGui::SameLine();

		std::vector<std::string>items = { obf("Toggle"), obf("Hold") };
		ImGuiHelper::renderCombo(" ", items, aimAssistOnHold, 80);

		ImGui::Hotkey(obf("Hotkey").c_str(), aimAssistKey);

		std::vector<std::string>items1 = { obf("By Distance"), obf("By Health") };
		ImGuiHelper::renderCombo(obf("Target Selection"), items1, aimTargetSelection, elementSize);
		std::string targets = "";
		if (!isAimEnemyTarget && !isAimMateTarget && !isAimBotTarget) targets = obf("None");
		else if (isAimEnemyTarget && isAimMateTarget && isAimBotTarget) targets = obf("All");
		else {
			if (isAimEnemyTarget) targets += obf("Enemy,").c_str();
			if (isAimMateTarget) targets += obf("Mate,").c_str();
			if (isAimBotTarget) targets += obf("Bots,").c_str();
			if (targets.back() == ',') targets.pop_back(); // remove , at the end
		}
		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo(obf("Targets").c_str(), targets.c_str(), 0)) {
			ImGui::Checkbox_(obf("Enemy").c_str(), &isAimEnemyTarget);
			ImGui::Checkbox_(obf("Mate").c_str(), &isAimMateTarget);
			ImGui::Checkbox_(obf("Bot").c_str(), &isAimBotTarget);
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		std::vector<std::string>items2 = { obf("Head"), obf("Neck"), obf("Body"), obf("Arms"), obf("Hip"), obf("Legs") };
		ImGuiHelper::renderCombo(obf("Hitbox"), items2, aimHitbox, elementSize);

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderInt_2(obf("Reaction ms").c_str(), &reactionms, 0, 1000);
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderInt_2(obf("FOV").c_str(), &fov, 0, 180);
		ImGui::PopItemWidth();
		ImGui::Checkbox_(obf("Relative FOV").c_str(), &relativeFOV);
		ImGui::Checkbox_(obf("No Snap").c_str(), &noAimSnap);
		ImGui::Checkbox_(obf("No Lock").c_str(), &noAimLock);
		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild(obf("aimassist2").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::Checkbox_(obf("Enable Recoil Control").c_str(), &isRCS);
		ImGui::Checkbox_(obf("Standalone").c_str(), &standaloneRCS);

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderFloat_(obf("X Strength").c_str(), &rcsXStrength, 0.1, 1);
		ImGui::SliderFloat_(obf("Y Strength").c_str(), &rcsYStrength, 0.1, 1);
		ImGui::PopItemWidth();

		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild(obf("aimassist3").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
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
	std::vector<std::string> arr = { obf("ESP"), obf("World"), obf("Other") };
	ImGuiHelper::drawTabHorizontally(obf("subtab-1"), ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab1);
	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild(obf("modules-wrapper").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab1) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild(obf("esp").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::Checkbox_(obf("Enabled").c_str(), &isESPEnabled);

		ImGui::Hotkey(obf("Hotkey").c_str(), espKey);

		std::vector<std::string>items1 = { obf("Enemy"),obf("Mate"), obf("Bot") };
		ImGuiHelper::renderCombo(obf("Type"), items1, espType, elementSize);
		ImGui::ColorEdit4(obf("ESP Color##1").c_str(), (float*)&espCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

		std::string style = obf("Style");
		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo(obf("Style").c_str(), style.c_str(), 0)) {
			ImGui::Checkbox_(obf("2D Box").c_str(), &espShow2D);
			ImGui::Checkbox_(obf("Skeleton").c_str(), &espShowSkeleton);
			ImGui::Checkbox_(obf("Healthbar").c_str(), &espShowHealth);
			ImGui::Checkbox_(obf("Head Circle").c_str(), &espShowHeadCircle);

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::Checkbox_(obf("Based on Health").c_str(), &espColByHealth);

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild(obf("Markers").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::Checkbox_(obf("Enable Markers").c_str(), &isESPMarkers);
		ImGui::ColorEdit4(obf("Marker Color##1").c_str(), (float*)&markerCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild(obf("esp2").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
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
	std::vector<std::string> arr = { obf("General"), obf("Other") };
	ImGuiHelper::drawTabHorizontally(obf("subtab-2"), ImVec2(ImGuiHelper::getWidth(), 50), arr, selectedSubTab2);

	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild(obf("modules-wrapper").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab2) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild(obf("misc##0-0").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::Checkbox_(obf("Show Module List").c_str(), &isModuleList);
		ImGui::ColorEdit4(obf("Background Color##1").c_str(), (float*)&moduleListBg, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		std::vector<std::string>items1 = { obf("ASC"), obf("DSC") };
		ImGuiHelper::renderCombo(obf("Sort"), items1, moduleListSortby, elementSize);

		std::vector<std::string>items2 = { obf("Left"), obf("Right"), obf("Middle") };
		ImGuiHelper::renderCombo(obf("Align"), items2, moduleListAlign, elementSize);

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild(obf("misc##0-1").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild(obf("misc##0-2").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();
		break;
	}
	case 1: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild(obf("gui").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, 300), true);
		ImGui::ColorEdit4(obf("Window Color##1").c_str(), (float*)&winCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("BackGround Color##1").c_str(), (float*)&childCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("Frame Color##1").c_str(), (float*)&frameCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("Button Color##1").c_str(), (float*)&bgCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("Button Hovered Color##1").c_str(), (float*)&btnHoverCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("Button Active Color##1").c_str(), (float*)&btnActiveCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("Item Color##1").c_str(), (float*)&itemCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::ColorEdit4(obf("Item Active Color##1").c_str(), (float*)&itemActiveCol, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);

		setColors(); // not optimal to call all at once but this should be no problem to handle

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild(obf("smth").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild(obf("whoknows").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), true);
		ImGui::EndChild();
		break;
	}
	}

	ImGui::EndChild();
}

void Menu::renderSubTab3() {
	ImGui::BeginChild(obf("config-tab").c_str(), ImVec2(ImGui::GetContentRegionAvail().x, ImGui::GetContentRegionAvail().y), false);

	ImGui::EndChild();
}

void Menu::render() {
	renderModules();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		isGUIVisible = !isGUIVisible;
	}

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
			ImGui::Text(obf("Recoil Control").c_str());
		if (isAimAssistEnabled)
			ImGui::Text(obf("AimAssist").c_str());
		if (isESPEnabled)
			ImGui::Text(obf("ESP").c_str());
	}

	ImGui::End();
}