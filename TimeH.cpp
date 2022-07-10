#include "TimeH.hpp"

#include <chrono>

std::string TimeH::getHourMinutesSeconds() {
	struct tm tstruct;
	time_t now = time(0);
	localtime_s(&tstruct, &now);

	char buf[10];
	std::strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);

	return buf;
}