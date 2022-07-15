#pragma once

#include "Obf.hpp"
#include <string>
#include <vector>

namespace FileH {

	// Folder names located in %APPDATA%
	static std::string PATHNAME = obf("\\ImGuiCheat");
	static std::string CFGNAME = obf("\\cfgs");

	std::string getFilePath();
	std::string getDirPath();
	std::string getTempPath();
	std::string getRoamingPath();

	std::string getProjPath();
	std::string getProjCfgPath();
	std::vector<std::string> getFilesInDir(std::string path);

	bool deleteFile(std::string filePath);
};