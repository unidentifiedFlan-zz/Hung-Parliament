#pragma once
#include "politician.h"

class Conversation
{
	Politician *mp_;
	HistoryLogger<std::string, const Idea*> *seenIdeas_;

public:
	Conversation(Politician *mp, HistoryLogger<std::string, const Idea*> *seenIdeas, const Idea legislation);
	void suggestIdea();
	void getCurrentIdeas();
	void endConversation();
	void getHelp();
	~Conversation();
};

