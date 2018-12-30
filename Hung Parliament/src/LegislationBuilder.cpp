#include "legislationBuilder.h"

LegislationBuilder::LegislationBuilder(std::vector<std::string> &characteristicNames) : IdeaBuilder(characteristicNames)
{
}

tinyxml2::XMLError LegislationBuilder::loadFile() {
	return doc.LoadFile("xml/Legislation.xml");
}

LegislationBuilder::~LegislationBuilder()
{
}
