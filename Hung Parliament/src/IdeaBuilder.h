#pragma once
#include "stdafx.h"
#include "Idea.h"
#include "Opinion.h"
#include "tinyxml2.h"

class IdeaBuilder
{
protected:
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *idea;
	std::vector<std::string> characteristicNames;

	std::vector<Idea> ideas;

	const bool initParser();
	virtual tinyxml2::XMLError loadFile();
	std::string parseIdeaName();
	std::string parseText(tinyxml2::XMLElement *root);
	Characteristics parseCharacteristics(tinyxml2::XMLElement *root);
	std::vector<Opinion> parseOpinions();
public:
	IdeaBuilder(std::vector<std::string> &characteristicNames);
	std::vector<Idea> build(int numIdeas);
	virtual ~IdeaBuilder();
};

