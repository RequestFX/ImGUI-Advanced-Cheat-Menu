#pragma once
#include "../Singleton.hpp"
#include "Fonts.hpp"

#include <vector>
#include <string>


struct Output {
	std::string text, time;
	bool drawTime;
	int type;

	Output(std::string text_, bool drawTime_, int type_) {
		text = text_;
		drawTime = drawTime_;
		type = type_;
	}
};

class Console : public Singleton<Console> {
	friend class Singleton<Console>;

	void renderLog(Output& output);
	void renderLogError(Output& output);
	void renderLogInfo(Output& output);

public:
	int selectedTypeTab;
	std::vector<std::string> types{ ICON_FA_LIST_ALT " All", ICON_FA_TIMES_CIRCLE " Errors", ICON_FA_INFO_CIRCLE " Info" };

	char inputBuf[256];
	std::vector<Output> outputArr;

	bool DRAW_CONSOLE = true;

	void render();

	void log(const char*, bool printTime = true);
	void logError(const char*, bool printTime = true);
	void logInfo(const char*, bool printTime = true);
};