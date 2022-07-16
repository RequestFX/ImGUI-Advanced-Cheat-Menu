#pragma once
#include "util/Obf.hpp"
#include "util/StringH.hpp"
#include "util/Vec2H.hpp"
#include "menu/Console.hpp"

#include <string>

class Module {
private:
	std::string name, description;
	bool toggled;
	int key;
public:

	Module(std::string name, std::string description, int key = 0) {
		this->name = name;
		this->description = description;

		this->key = key;
		this->toggled = false;
	}

	virtual void onEnable() = 0;
	virtual void onDisable() = 0;

	std::string& getName() {
		return name;
	}

	std::string& getDescription() {
		return description;
	}

	int& getKey() {
		return key;
	}

	void setKey(int key, bool log = false) {
		this->key = key;
		if (!log) return;
		std::string out = obf("Set Key: [").c_str() + StringH::vkToString(key) + obf("] for Module: [").c_str() + this->name.c_str() + "]";
		Console::i().logInfo(out);
	}

	bool& isToggled() {
		return toggled;
	}

	void setToggled(bool toggled, bool log = false) {
		this->toggled = toggled;
		if (!log) return;
		Console::i().logInfo(obf("Set Toggled: [") + StringH::boolToStr(toggled) + obf("] for Module: [") + this->name + obf("]"));
	}

	void toggle(bool log = false) {
		toggled = !toggled;
		if (isToggled()) {
			onEnable();
		}
		else {
			onDisable();
		}
		if (!log) return;

		Console::i().logInfo(obf("Toggled to: [") + StringH::boolToStr(toggled) + obf("] for Module: [") + this->name + obf("]"));
	}
};