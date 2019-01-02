#pragma once
#include "politician.h"

class Conversation
{
	Politician *mp_;
	HistoryLogger<std::string, const Idea*> *seenIdeas_;
	const Idea legislation_;

	std::string introduction();
	void processCommands();
	void suggestIdea();
	void getCurrentIdeas();
	void endConversation();
	void getHelp();
	std::string streamMP(std::string output);
	std::string streamOutput(std::string output);
	std::string streamCommand();

public:
	Conversation(Politician *mp, HistoryLogger<std::string, const Idea*> *seenIdeas, const Idea legislation);
	~Conversation();
};

