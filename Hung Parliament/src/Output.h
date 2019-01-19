#pragma once

#include "stdafx.h"

class Output
{
	static std::string command();
public:
	Output();

	static std::string general(std::string output);
	static std::string politician(std::string output, std::string name);
	static std::string whip(std::string output);
	static std::string whipEvent(std::string output);
	static void switchToConversation();
	static void switchToMainInterface();
	~Output();
};