#include "imgui.h"
#include "imgui-SFML.h"
#include "util/Obf.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "menu/Fonts.hpp"
#include "menu/Menu.hpp"
#include "menu/Console.hpp"
#include "ModuleManager.hpp"

#include <Windows.h>
#include "menu/imgui_notify.h"

bool show_demo_window = true;

void keyCheck() {
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		Menu::isGUIVisible = !Menu::isGUIVisible;
	}

	for (Module* mod : ModuleManager::i().modules) {
		if (GetAsyncKeyState(mod->getKey()) & 1) {
			mod->toggle();
			ImGuiToast toast(ImGuiToastType_Info, 400);
			toast.set_title((obf("Toggled ") + mod->getName()).c_str());
			ImGui::InsertNotification(toast);
		}
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	sf::RenderWindow window(sf::VideoMode(1280, 800), obf("ImGui + SFML = <3"), sf::Style::Default);
	HWND hwnd = window.getSystemHandle();
	//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW); // exclude from taskbar
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	// Setup our Menu Theme and font
	Menu::loadTheme();

	Console::i().log(obf("Test Log"));
	Console::i().logInfo(obf("Info Test Log"));
	Console::i().logError(obf("Error Test Log"));
	Console::i().log(obf("Log with no Date"), false);

	Console::i().logInfo(obf("sdcfg -> Save Current Config"));
	Console::i().logInfo(obf("ldcfg -> Load Saved Config"));

	sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(window, event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		ImGui::SFML::Update(window, deltaClock.restart());

		keyCheck();

		// imgui render here
		if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		Menu::render();
		if (Menu::isGUIVisible)
			Console::i().render();

		{ // render Notifications
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f);
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));
			ImGui::RenderNotifications();
			ImGui::PopStyleVar(1); // Don't forget to Pop()
			ImGui::PopStyleColor(1);
		}

		window.clear(sf::Color(115, 140, 155, 255));
		// sfml render here

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}