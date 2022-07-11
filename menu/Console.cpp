#include "Console.hpp"
#include "../util/TimeH.hpp"
#include "../util/Obf.hpp"

#include "imgui_custom.hpp"
#include <SFML/Graphics.hpp>

void Console::renderLog(Output& output) {
	if (output.type != 0) return;
	std::string print = output.text;
	if (output.drawTime) print = "[" + output.time + "] " + print;
	ImGui::TextUnformatted(print.c_str());
}
void Console::renderLogError(Output& output) {
	if (output.type != 1) return;
	std::string print = output.text;
	if (output.drawTime) print = "[" + output.time + "] " ICON_FA_TIMES_CIRCLE + " " + print;
	ImVec4 color = ImGuiHelper::rgbaToVec4(255, 152, 172, 255);

	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopStyleColor();
}
void Console::renderLogInfo(Output& output) {
	if (output.type != 2) return;
	std::string print = output.text;
	if (output.drawTime) print = "[" + output.time + "] " ICON_FA_INFO_CIRCLE + " " + print;
	ImVec4 color = ImGuiHelper::rgbaToVec4(122, 202, 242, 255);

	ImGui::PushStyleColor(ImGuiCol_Text, color);
	ImGui::TextUnformatted(print.c_str());
	ImGui::PopStyleColor();
}

void Console::render() {
	if (!DRAW_CONSOLE) return;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, { 300,200 });
	ImGui::Begin("   ", 0, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
	ImGui::PopStyleVar();

	ImGuiHelper::drawTabHorizontally(obf("Styles"), ImVec2(ImGuiHelper::getWidth(), 50), types, selectedTypeTab);

	const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
	ImGui::BeginChild(obf("ScrollingRegion").c_str(), ImVec2(0, -footer_height_to_reserve), true, ImGuiWindowFlags_HorizontalScrollbar);

	for (int i = 0; i < outputArr.size(); i++) { // draw output
		Output output = outputArr.at(i);

		if (selectedTypeTab == 0) { // draw all
			renderLog(output);
			renderLogError(output);
			renderLogInfo(output);
		}
		else if (selectedTypeTab == 1) {
			renderLogError(output);
		}
		else if (selectedTypeTab == 2) {
			renderLogInfo(output);
		}
	}

	if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) ImGui::SetScrollHereY(1.0f); // scroll down automatically

	ImGui::EndChild();
	ImGui::Separator();

	bool reclaim_focus = false;
	ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
	if (ImGui::InputText(obf("Input").c_str(), inputBuf, sizeof(inputBuf), input_text_flags)) {
		std::string s = inputBuf;
		memset(inputBuf, 0, sizeof(inputBuf));
		if (s.compare(obf("clear").c_str()) == 0 || s.compare(obf("cls").c_str()) == 0) outputArr.clear();

		reclaim_focus = true;
	}

	// Auto-focus on window apparition
	ImGui::SetItemDefaultFocus();
	if (reclaim_focus)
		ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

	ImGui::End();

}

void Console::log(std::string text, bool printTime) {
	Output output{ text, printTime, 0 };
	if (printTime) output.time = TimeH::getHourMinutesSeconds();

	outputArr.push_back(output);
}

void Console::logError(std::string text, bool printTime) {
	Output output{ text, printTime, 1 };
	if (printTime) output.time = TimeH::getHourMinutesSeconds();

	outputArr.push_back(output);
}

void Console::logInfo(std::string text, bool printTime) {
	Output output{ text, printTime, 2 };
	if (printTime) output.time = TimeH::getHourMinutesSeconds();

	outputArr.push_back(output);
}