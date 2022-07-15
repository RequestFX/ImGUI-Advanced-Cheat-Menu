#include "Config.hpp"
#include "util/FileH.hpp"
#include "ModuleManager.hpp"
#include "SetManager.hpp"

#include "menu/imgui_helper.hpp"
#include "menu/Menu.hpp"

#include <fstream>

Config::Config() {
	checkCfgs(); // adds available configs into the list
}

bool Config::save() {
	return save(FileH::getProjCfgPath() + obf("\\DefaultCfg.ini"));
}
bool Config::save(std::string filePath) {
	std::ofstream save(filePath);
	if (!save.is_open()) return false;

	for (Module* mod : ModuleManager::i().modules) {
		std::string str = obf("MOD:") + mod->getName() + ":" + std::to_string(mod->isToggled()) + ":" + std::to_string(mod->getKey());
		str = Obf::xor_(str);

		save << StringH::strToBytes(str) << "\n";
	}

	for (Set* set : SetManager::i().settings) {
		bool isID2 = !set->ID2.empty();
		std::string str = std::to_string(isID2) + ":" + set->ID + ":" + (isID2 ? (set->ID2 + ":") : "");
		str = obf("SET:") + str;

		if (set->isBool()) {
			str += std::to_string(set->getBVal());
		}
		else if (set->isInt()) {
			str += std::to_string(set->getIVal());
		}
		else if (set->isFloat()) {
			str += std::to_string(set->getFVal());
		}
		else if (set->isDouble()) {
			str += std::to_string(set->getDVal());
		}
		else if (set->isISlider()) {
			str += std::to_string(set->getVec3i().x) + ":" + std::to_string(set->getVec3i().y) + ":" + std::to_string(set->getVec3i().z);
		}
		else if (set->isFSlider()) {
			str += std::to_string(set->getVec3f().x) + ":" + std::to_string(set->getVec3f().y) + ":" + std::to_string(set->getVec3f().z);
		}
		else if (set->isDSlider()) {
			str += std::to_string(set->getVec3d().x) + ":" + std::to_string(set->getVec3d().y) + ":" + std::to_string(set->getVec3d().z);
		}
		else if (set->isVec4()) {
			str += std::to_string(set->getVec4().x) + ":" + std::to_string(set->getVec4().y) + ":" + std::to_string(set->getVec4().z) + ":" + std::to_string(set->getVec4().w);
		}

		str = Obf::xor_(str);
		save << StringH::strToBytes(str) << "\n";
	}

	save.close();
	return true;
}


bool Config::load() {
	return load(FileH::getProjCfgPath() + obf("\\DefaultCfg.ini"));
}

bool Config::load(std::string filePath) {
	std::ifstream load(filePath);
	if (!load.is_open())return false;

	std::vector<std::string> toLoad;
	std::string line;
	while (std::getline(load, line)) {
		toLoad.push_back(Obf::xor_(StringH::bytesToStr(line)));
	}

	for (std::string s : toLoad) {
		std::vector<std::string> lineArr = StringH::split(s, ":");

		if (lineArr[0] == "MOD") {
			Module* mod = ModuleManager::i().getModuleByName(lineArr[1]);
			if (!mod) continue; // if module is NULL continue
			mod->setToggled(std::atoi(lineArr[2].c_str()));
			int key = std::atoi(lineArr[3].c_str());
			mod->setKey(key, key != 0);
		}
		else if (lineArr[0] == "SET") {
			bool isID2 = std::atoi(lineArr[1].c_str());
			int idx = isID2 ? 4 : 3;
			Set* set = isID2 ? SetManager::i().getSetByName(lineArr[2], lineArr[3]) : SetManager::i().getSetByName(lineArr[2]);
			if (!set) continue; // if module is NULL continue

			try{

			if (set->isBool()) {
				set->setBVal(std::atoi(lineArr[idx].c_str()));
			}
			else if (set->isInt()) {
				set->setIVal(std::atoi(lineArr[idx].c_str()));
			}
			else if (set->isFloat()) {
				set->setFVal(std::atof(lineArr[idx].c_str()));
			}
			else if (set->isDouble()) {
				set->setDVal(std::atof(lineArr[idx].c_str()));
			}
			else if (set->isISlider()) {
				set->setVec3i(std::atoi(lineArr[idx].c_str()), std::atoi(lineArr[idx + 1].c_str()), std::atoi(lineArr[idx + 2].c_str()));
			}
			else if (set->isFSlider()) {
				set->setVec3f(std::atof(lineArr[idx].c_str()), std::atof(lineArr[idx + 1].c_str()), std::atof(lineArr[idx + 2].c_str()));
			}
			else if (set->isDSlider()) {
				set->setVec3d(std::atof(lineArr[idx].c_str()), std::atof(lineArr[idx + 1].c_str()), std::atof(lineArr[idx + 2].c_str()));
			}
			else if (set->isVec4()) {
				set->setVec4(ImVec4(std::atof(lineArr[idx].c_str()), std::atof(lineArr[idx + 1].c_str()), std::atof(lineArr[idx + 2].c_str()),std::atof(lineArr[idx + 3].c_str())));
			}

			}catch(...){}
		}
	}
	load.close();

	Menu::setColors(); // update Colors

	return true;
}

void Config::renderImGui() {
	checkCfgs(); // TODO: load on config change events

	ImGui::BeginChild(obf("config-tab").c_str(), ImVec2(ImGuiHelper::getWidth(), ImGuiHelper::getHeight()), true);

	for (int i = 0; i < cfgs.size(); i++) {
		std::string& cfg = cfgs.at(i);
		std::string cfgName = StringH::getFileNameFromPath(cfg);

		ImGui::PushStyleColor(ImGuiCol_ChildBg, *Menu::childCol1);
		ImGui::BeginChild((obf("Config##") + std::to_string(i)).c_str(), ImVec2(ImGuiHelper::getWidth(), 80), true);
		ImGui::PopStyleColor();

		ImGui::Text(cfgName.c_str());
		ImGui::SameLine();
		if (ImGui::Button("Load")) {
			load(cfg);
		}
		ImGui::SameLine();
		if (ImGui::Button("Save")) { // TODO: confirmation Popup for overwriting Config
			save(cfg);
		}
		ImGui::SameLine();
		if (ImGui::Button("Rename")) { // TODO: Add Popup to Rename Config

		}
		ImGui::SameLine();
		if (ImGui::Button("Delete")) { // TODO: confirmation Popup for deleting Config
			FileH::deleteFile(cfg);
		}

		ImGui::EndChild();
	}

	ImGui::EndChild();
}

void Config::checkCfgs() {
	cfgs = FileH::getFilesInDir(FileH::getProjCfgPath());
}