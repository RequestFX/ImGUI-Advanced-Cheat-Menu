#include "Menu.hpp"
#include "../HUD.hpp"
#include "../RCS.hpp"
#include "../ESP.hpp"
#include "../Marker.hpp"
#include "../AimAssist.hpp"
#include "../ModuleManager.hpp"

#include "../Config.hpp"
#include "../util/ColorH.hpp"
#include "../util/Obf.hpp"
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

		ImGui::BeginChild(obf("aimassist").c_str(), ImVec2(ImGuiHelper::getWidth(), 300), true);
		ImGui::Checkbox_(obf("Enabled").c_str(), &AimAssist::i().isToggled());
		ImGui::SameLine();

		int i = *AimAssist::i().onHold;

		ImGuiHelper::renderCombo(" ", { obf("Toggle"), obf("Hold") }, *AimAssist::i().onHold, 80);

		ImGui::Hotkey(obf("Hotkey").c_str(), AimAssist::i().getKey());

		ImGuiHelper::renderCombo(obf("Target Selection"), { obf("By Distance"), obf("By Health") }, *AimAssist::i().targetSelection, elementSize);
		std::string targets = "";
		if (AimAssist::i().isEnemy || AimAssist::i().isMate || AimAssist::i().isBot) { // atleast one target
			if (AimAssist::i().isEnemy && AimAssist::i().isMate && AimAssist::i().isBot) targets = obf("All");
			else {
				if (AimAssist::i().isEnemy) targets += obf("Enemy,").c_str();
				if (AimAssist::i().isMate) targets += obf("Mate,").c_str();
				if (AimAssist::i().isBot) targets += obf("Bots,").c_str();
				if (targets.back() == ',') targets.pop_back(); // remove , at the end
			}
		}
		else targets = obf("None");

		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo(obf("Targets").c_str(), targets.c_str(), 0)) {
			ImGui::Checkbox_(obf("Enemy").c_str(), AimAssist::i().isEnemy);
			ImGui::Checkbox_(obf("Mate").c_str(), AimAssist::i().isMate);
			ImGui::Checkbox_(obf("Bot").c_str(), AimAssist::i().isBot);
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGuiHelper::renderCombo(obf("Hitbox"), { obf("Head"), obf("Neck"), obf("Body"), obf("Arms"), obf("Hip"), obf("Legs") }, *AimAssist::i().hitbox, elementSize);

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderInt_(obf("Reaction ms").c_str(), AimAssist::i().reactionTime, 0, 1000);
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderInt_(obf("FOV").c_str(), AimAssist::i().fov, 0, 360);
		ImGui::PopItemWidth();
		ImGui::Checkbox_(obf("Relative FOV").c_str(), AimAssist::i().relativeFOV);
		ImGui::Checkbox_(obf("No Snap").c_str(), AimAssist::i().noSnap);
		ImGui::Checkbox_(obf("No Lock").c_str(), AimAssist::i().noLock);
		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild(obf("aimassist2").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::Checkbox_(obf("Enable Recoil Control").c_str(), &RCS::i().isToggled());
		ImGui::Checkbox_(obf("Standalone").c_str(), RCS::i().standalone);

		ImGui::PushItemWidth(elementSize);
		ImGui::SliderFloat_(obf("X Strength").c_str(), &RCS::i().xPow->x, 0.1, 1);
		ImGui::SliderFloat_(obf("Y Strength").c_str(), &RCS::i().yPow->x, 0.1, 1);
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
	ImGuiHelper::drawTabHorizontally(obf("subtab-1"), ImVec2(ImGuiHelper::getWidth(), 50), { obf("ESP"), obf("World"), obf("Other") }, selectedSubTab1);
	ImGui::Spacing();

	ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 0));
	ImGui::BeginChild(obf("modules-wrapper").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab1) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild(obf("esp").c_str(), ImVec2(ImGuiHelper::getWidth(), 300), true);
		ImGui::Checkbox_(obf("Enabled").c_str(), &ESP::i().isToggled());

		ImGui::Hotkey(obf("Hotkey").c_str(), ESP::i().getKey());

		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo(obf("Type").c_str(), obf("Type").c_str(), 0)) {
			ImGui::Checkbox_(obf("Enemy").c_str(), ESP::i().isEnemy);
			ImGui::Checkbox_(obf("Mate").c_str(), ESP::i().isMate);
			ImGui::Checkbox_(obf("Bot").c_str(), ESP::i().isBot);

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo(obf("2D Box Style").c_str(), obf("Style").c_str(), 0)) {
			ImGui::Checkbox_(obf("2D Box").c_str(), ESP::i().is2DBox);
			ImGui::ColorEdit4(obf("2D Box Color##1").c_str(), (float*)ESP::i().col2DBox, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox_(obf("2D Box Based on Health").c_str(), ESP::i().is2DBoxHealthBased);
			ImGui::EndCombo();
		}
		if (ImGui::BeginCombo(obf("Skeleton Style").c_str(), obf("Style").c_str(), 0)) {
			ImGui::Checkbox_(obf("Skeleton").c_str(), ESP::i().isSkeleton);
			ImGui::ColorEdit4(obf("Skeleton Color##1").c_str(), (float*)ESP::i().colSkeleton, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox_(obf("Skeleton Based on Health").c_str(), ESP::i().isSkeletonHealthBased);
			ImGui::EndCombo();
		}
		if (ImGui::BeginCombo(obf("Healthbar Style").c_str(), obf("Style").c_str(), 0)) {
			ImGui::Checkbox_(obf("Healthbar").c_str(), ESP::i().isHealthBar);
			ImGui::ColorEdit4(obf("Healthbar Color##1").c_str(), (float*)&ESP::i().colHealthBar, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox_(obf("Healthbar Based on Health").c_str(), ESP::i().isHealthBarHealthBased);
			ImGui::EndCombo();
		}
		if (ImGui::BeginCombo(obf("Head Circle Style").c_str(), obf("Style").c_str(), 0)) {
			ImGui::Checkbox_(obf("Head Circle").c_str(), ESP::i().isHeadCircle);
			ImGui::ColorEdit4(obf("Head Circle Color##1").c_str(), (float*)ESP::i().colHeadCircle, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox_(obf("Head Circle Based on Health").c_str(), ESP::i().isHeadCircleHealthBased);
			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::EndChild();

		ImGui::Spacing();

		ImGui::BeginChild(obf("Markers").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::Checkbox_(obf("Enable Markers").c_str(), &Marker::i().isToggled());
		ImGui::ColorEdit4(obf("Marker Color##1").c_str(), (float*)Marker::i().col, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
		ImGui::Checkbox_(obf("Render Behind").c_str(), Marker::i().renderBehind);
		ImGui::Checkbox_(obf("Render Infront").c_str(), Marker::i().renderInfront);
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
	ImGui::BeginChild(obf("modules-wrapper").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), false);
	ImGui::PopStyleColor();

	switch (selectedSubTab2) {
	case 0: {
		ImGui::Columns(2, nullptr, false);
		ImGui::SetColumnOffset(1, 300);

		ImGui::BeginChild(obf("misc##0-0").c_str(), ImVec2(ImGuiHelper::getWidth(), 300), true);
		ImGui::Checkbox_(obf("Show HUD").c_str(), &HUD::i().isToggled());
		ImGui::Checkbox_(obf("Show ModuleList").c_str(), HUD::i().isML);
		ImGui::PushItemWidth(elementSize);
		if (ImGui::BeginCombo(obf("ModuleList Style").c_str(), obf("Style").c_str(), 0)) {
			ImGui::ColorEdit4(obf("ModuleList Color##1").c_str(), (float*)&HUD::i().colML->x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			ImGui::Checkbox_(obf("Rainbow Color").c_str(), HUD::i().isMLRainbow);
			ImGui::PushItemWidth(elementSize);
			ImGui::SliderFloat_(obf("ModuleList Speed").c_str(), &HUD::i().speedML->x, 0.1, 1);
			ImGui::SliderFloat_(obf("ModuleList Offset").c_str(), &HUD::i().offsetML->x, 0, 0.4);
			ImGui::SliderFloat_(obf("ModuleList Range").c_str(), &HUD::i().rangeML->x, 0, 0.1);
			ImGui::PopItemWidth();
			ImGui::ColorEdit4(obf("Background Color##1").c_str(), (float*)&HUD::i().colML_Bg->x, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_AlphaBar);
			ImGuiHelper::renderCombo(obf("Sort"), { obf("ASC"), obf("DSC") }, *HUD::i().sortML, elementSize);
			ImGuiHelper::renderCombo(obf("Align"), { obf("Left"), obf("Right"), obf("Middle") }, *HUD::i().alignML, elementSize);

			ImGui::EndCombo();
		}
		ImGui::PopItemWidth();

		ImGui::EndChild();
		ImGui::Spacing();

		ImGui::BeginChild(obf("misc##0-1").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild(obf("misc##0-2").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
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

		ImGui::BeginChild(obf("smth").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::EndChild();

		ImGui::NextColumn();

		ImGui::BeginChild(obf("whoknows").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);
		ImGui::EndChild();
		break;
	}
	}

	ImGui::EndChild();
}

void Menu::render() {
	HUD::i().render();

	if (GetAsyncKeyState(VK_INSERT) & 1) {
		isGUIVisible = !isGUIVisible;
	}

	if (!isGUIVisible) return;

	ImGui::SetNextWindowSize({ 800, 600 });
	ImGui::Begin(" ", 0, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

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
			Config::i().renderImGui();// for config, save current(new), load, delete, duplicate, overwrite
			break;
		}
		}
	}
	ImGui::End();
}