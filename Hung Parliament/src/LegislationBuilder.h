#pragma once
#include "stdafx.h"
#include "IdeaBuilder.h"

class LegislationBuilder : public IdeaBuilder
{
	tinyxml2::XMLError loadFile();
public:
	LegislationBuilder(std::vector<std::string> &characteristicNames);

	~LegislationBuilder();
};

