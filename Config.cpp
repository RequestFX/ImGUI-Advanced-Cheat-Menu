#include "Config.hpp"
#include "util/FileH.hpp"
#include "ModuleManager.hpp"

#include <fstream>

bool Config::save() {
	std::ofstream save(FileH::getProjectPath() + obf("\\DefaultCfg.ini"));
	if (!save.is_open()) return false;

	for (Module* mod : ModuleManager::i().modules) {
		std::string s = obf("MOD:") + mod->getName() + ":" + std::to_string(mod->isToggled()) + ":" + std::to_string(mod->getKey());
		s = Obf::xor_(s);

		save << StringH::strToBytes(s) << "\n";
	}
	save.close();

	return true;
}
bool Config::load() {
	std::ifstream load(FileH::getProjectPath() + obf("\\DefaultCfg.ini"));
	if (!load.is_open())return false;

	std::vector<std::string> toLoad;
	std::string line;
	while (std::getline(load, line)) {
		toLoad.push_back(Obf::xor_(StringH::bytesToStr(line)));
	}

	for (std::string s : toLoad) {
		std::vector<std::string> lineArr = StringH::split(s, ":");

		if (lineArr[0] == "MOD") {
			Module* m = ModuleManager::i().getModuleByName(lineArr[1]);
			if (m != NULL) {
				m->setToggled(std::atoi(lineArr[2].c_str()));
				int key = std::atoi(lineArr[3].c_str());
				m->setKey(key, key != 0);
			}
		}
	}
	load.close();

	return true;
}