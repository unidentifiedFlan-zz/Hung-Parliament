#pragma once

#include "stdafx.h"
#include "Conversation.h"
#include "Whip.h"

class userCommands
{
public:
	userCommands();
	static bool mp(std::string &cmd);
	static bool findMP(std::string &cmd);
	static bool getAdvice(std::string &cmd);
	static bool getLegislationInformation(std::string &cmd);
	static bool getStatistics(std::string &cmd);
	static bool getOverview(std::string &cmd);
	static bool idea(std::string &cmd);
	static bool getListOfIdeas(std::string &cmd);
	static bool getSupport(std::string &cmd);
	static bool suggestIdea(std::string &cmd);
	static bool getIdeas(std::string &cmd);
	static bool quit(std::string &cmd);
	static bool help(std::string &cmd);
	~userCommands();
};

