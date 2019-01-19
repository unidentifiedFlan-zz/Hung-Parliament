#pragma once
#include "stdafx.h"
#include "Parliament.h"
#include "Output.h"

class Whip : public Listener
{
	Parliament *parliament_;
	PoliticianLists lists_;

	std::map<Politician*, bool> support_;
	int numMPsSupportingLegislation_ = 0;

	int calculateTotalLegislationSupport();
	std::string updateLegislationSupport(Politician *mp);
	std::string getCharacteristicDetails(Characteristics &characs);
public:
	Whip(Parliament *parliament, PoliticianLists& lists);
	void handleEvent(Event &e);

	std::string getAdvice();
	std::string getStatistics();
	std::string getTimeRemaining();
	std::string describeLegislation();
	Idea getLegislation();

	Politician* findMP(std::string &mp);
	std::string getMPDetails(const Politician *mp);
	std::string getIdeaDetails(const Idea *idea);
	~Whip();
};

