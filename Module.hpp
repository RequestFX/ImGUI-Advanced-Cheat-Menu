#pragma once
#include "util/Obf.hpp"
#include "util/StringUtil.hpp"
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

	void setKey(int key) {
		this->key = key;
		std::string out = obf("Set Key: [").c_str() + StringUtil::vkToString(key) + obf("] for Module: [").c_str() + this->name.c_str() + "]";
		Console::get().logInfo(out);
	}

	bool& isToggled() {
		return toggled;
	}

	void setToggled(bool toggled) {
		this->toggled = toggled;
		Console::get().logInfo(obf("Set Toggled: [") + StringUtil::boolToStr(toggled) + obf("] for Module: [") + this->name + obf("]"));
	}

	void toggle() {
		toggled = !toggled;
		Console::get().logInfo(obf("Toggled to: [") + StringUtil::boolToStr(toggled) + obf("] for Module: [") + this->name + obf("]"));

		if (isToggled()) {
			onEnable();
		}
		else {
			onDisable();
		}
	}
};