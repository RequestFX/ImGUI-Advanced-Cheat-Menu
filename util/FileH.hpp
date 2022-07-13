#pragma once

#include "Obf.hpp"
#include <string>

namespace FileH {

	static std::string PATHNAME = obf("\\ImGuiCheat");

	std::string getFilePath();
	std::string getDirPath();
	std::string getTempPath();
	std::string getRoamingPath();

	std::string getProjectPath();
};