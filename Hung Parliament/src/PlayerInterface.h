#pragma once

#include "stdafx.h"
#include "Output.h"
#include "Whip.h"

class PlayerInterface
{
	Whip *whip_;
	HistoryLogger<std::string, Idea> seenIdeas_;

	std::string introduction();
	void applyCommand(std::string &cmd, bool *quit);
	void getInformation(std::string &cmd);
	void startConversation();
	void speakToMP(Politician* mp);
	void getStatistics();
	void getIdeaDetails();
	void getMPDetails();
	std::string getHelp();
	bool confirmQuit(bool *quit);

public:
	PlayerInterface(Whip *whip);
	void waitForCommand(bool *quit);
	~PlayerInterface();
};

