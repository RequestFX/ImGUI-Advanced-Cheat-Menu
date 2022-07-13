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
#include <Windows.h>

bool show_demo_window = true;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	sf::RenderWindow window(sf::VideoMode(1280, 800), obf("ImGui + SFML = <3"), sf::Style::Default);
	HWND hwnd = window.getSystemHandle();
	//SetWindowLong(hwnd, GWL_EXSTYLE, GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_TOOLWINDOW); // exclude from taskbar
	window.setFramerateLimit(60);
	ImGui::SFML::Init(window);

	// Setup our Menu Theme and font
	Menu::loadTheme();

	Console::get().log(obf("HELLO WORLD!"));
	Console::get().log(obf("Some Other Text"));
	Console::get().logInfo(obf("Some Info Text :)"));
	Console::get().logError(obf("Error Message :("));
	Console::get().log(obf("A Log without Date"), false);

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

		// imgui render here
		if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

		Menu::render();
		Console::get().render();

		window.clear(sf::Color(115, 140, 155, 255));
		// sfml render here

		ImGui::SFML::Render(window);
		window.display();
	}

	ImGui::SFML::Shutdown();
}