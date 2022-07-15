#include "FileH.hpp"

#include <Windows.h>
#include <filesystem>

namespace fs = std::filesystem;

std::string FileH::getFilePath() {
	char buffer[MAX_PATH] = { 0 };
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return std::string(buffer);
}

std::string FileH::getDirPath() {
	std::string filePath = getFilePath();
	return std::string(filePath).substr(0, std::string(filePath).find_last_of("\\"));
}

std::string FileH::getTempPath() {
	char buffer[MAX_PATH] = { 0 };
	GetTempPathA(MAX_PATH, buffer);
	return std::string(buffer).substr(0, std::string(buffer).find_last_of("\\"));
}

std::string FileH::getRoamingPath() {

	char* path;
	size_t requiredSize;

	getenv_s(&requiredSize, NULL, 0, obf("APPDATA").c_str());
	if (requiredSize == 0) {
		MessageBoxA(0, obf("Failed to get APPDATA Path!").c_str(), 0, 0);
		exit(1);
	}
	path = (char*)malloc(requiredSize * sizeof(char));
	if (!path) {
		MessageBoxA(0, obf("Failed to get allocate Memory!").c_str(), 0, 0);
		exit(1);
	}
	getenv_s(&requiredSize, path, requiredSize, obf("APPDATA").c_str());
	return path;
}

std::string FileH::getProjPath() {
	std::string roaming = getRoamingPath() + PATHNAME;
	if (!fs::exists(roaming))
		if (!fs::create_directory(roaming)) {
			roaming = obf("Failed to create a Folder at: ").c_str() + roaming;
			MessageBoxA(0, roaming.c_str(), 0, 0);
			exit(1);
		}

	return roaming;
}

std::string FileH::getProjCfgPath() {
	std::string cfgFolder = getProjPath() + CFGNAME;
	if (!fs::exists(cfgFolder))
		if (!fs::create_directory(cfgFolder)) {
			cfgFolder = obf("Failed to create a Folder at: ").c_str() + cfgFolder;
			MessageBoxA(0, cfgFolder.c_str(), 0, 0);
			exit(1);
		}

	return cfgFolder;
}

std::vector<std::string> FileH::getFilesInDir(std::string path) {
	std::vector<std::string> out;
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_regular_file()) out.push_back(entry.path().string());
	}
	return out;
}

bool FileH::deleteFile(std::string filePath) {
	if (fs::exists(filePath) && fs::is_regular_file(filePath)) {
		return fs::remove(filePath);
	}

	return false;
}