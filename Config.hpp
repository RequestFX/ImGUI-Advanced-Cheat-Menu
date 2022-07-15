#pragma once
#include "util/Singleton.hpp"

#include <string>
#include <vector>

class Config : public Singleton<Config> {
	friend class Singleton<Config>;
public:
	std::vector<std::string> cfgs;
	Config();

	void checkCfgs();
	void renderImGui();

	bool save();
	bool save(std::string filePath);
	bool load();
	bool load(std::string filePath);
};