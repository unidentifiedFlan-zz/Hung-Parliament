#pragma once
#include "stdafx.h"
#include "Ideas.h"
#include "Opinions.h"
#include "tinyxml2.h"
#include <random>

class IdeaBuilder
{
protected:
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *idea;
	std::vector<std::string> characteristicNames;

	Ideas ideas;

	const bool initParser();
	virtual tinyxml2::XMLError loadFile();
	std::string parseIdeaName();
	std::string parseText(tinyxml2::XMLElement *root);
	Characteristics parseCharacteristics(tinyxml2::XMLElement *root);
	Opinions parseOpinions();
	const unsigned int generateUniqueID();
public:
	IdeaBuilder(std::vector<std::string> &characteristicNames);
	Ideas build(const unsigned int &numIdeas);
	virtual ~IdeaBuilder();
};

