#pragma once

#include "stdafx.h"
#include "Politician.h"
#include "Whip.h"

class userCommands
{
	Whip * _whip;
	HistoryLogger<std::string, const Idea*> seenIdeas_;

	void applyCommand(std::string &cmd, bool *quit);
	void getInformation(std::string &cmd);
	bool findMP(std::string &cmd);
	bool requestAdvice(std::string &cmd);
	bool requestStatistics(std::string &cmd);
	bool requestQuit(std::string &cmd);
	bool requestHelp(std::string &cmd);
	void startConversation();
	void confirmQuit(bool *quit);
	void speakToMP(Politician* mp);
	void getStatistics();
	void getIdeaDetails();
	void getMPDetails();
	void getHelp();
public:
	userCommands(Whip* whip);
	void waitForCommand(bool *quit);
	~userCommands();
};
