#include "IdeaBuilder.h"
#include <chrono>

IdeaBuilder::IdeaBuilder(std::vector<std::string> &characNames) : characteristicNames(characNames) {}

tinyxml2::XMLError IdeaBuilder::loadFile() {
	return doc.LoadFile("xml/Ideas.xml");
}

const bool IdeaBuilder::initParser() {
	tinyxml2::XMLError error = loadFile();

	if (error) {
		std::cout << "Error: XML file is missing." << std::endl;
	}
	else {
		tinyxml2::XMLElement *root = doc.RootElement();
		if (root != nullptr) {

			idea = root->FirstChildElement("idea");
			return true;
		}
	}
	return false;
}

Ideas IdeaBuilder::build(const unsigned int &numIdeas) {

	ideas.clear();

	if (idea == nullptr && !initParser()) {
		return ideas;
	}

	for (unsigned int n = 0; idea && n < numIdeas; ++n) {

		std::string ideaName = parseIdeaName();
		std::string ideaDescription = parseText(idea);
		Characteristics ideaCharacs = parseCharacteristics(idea);

		Opinions opinionVector = parseOpinions();

		Idea newIdea(ideaName, ideaDescription, ideaCharacs, opinionVector);

		ideas.add(newIdea);
		
		idea = idea->NextSiblingElement("idea");
	}

	return ideas;
}


std::string IdeaBuilder::parseText(tinyxml2::XMLElement *root) {

	tinyxml2::XMLElement *text = root->FirstChildElement("text");
	if (text != nullptr) {
		return text->GetText();
	}
	return "";
}

std::string IdeaBuilder::parseIdeaName() {

	tinyxml2::XMLElement *name = idea->FirstChildElement("name");
	if (name != nullptr) {
		return name->GetText();
	}
	return "";
}

Characteristics IdeaBuilder::parseCharacteristics(tinyxml2::XMLElement *root) {

	std::vector<Characteristics::Characteristic> characVec;

	tinyxml2::XMLElement *characs = root->FirstChildElement("characteristics");
	if (characs != nullptr) {

		std::string::size_type size;
		for (std::vector<std::string>::iterator it = characteristicNames.begin(); it != characteristicNames.end(); ++it) {
			int value = 0;
			tinyxml2::XMLElement *charac = characs->FirstChildElement(it->c_str());
			if (charac != nullptr) {
				value = std::stoi(charac->GetText(), &size);
			}

			Characteristics::Characteristic newCh(*it, value);
			characVec.push_back(newCh);
		}

	}
	Characteristics newCharacs(characVec);

	return newCharacs;
}

Opinions IdeaBuilder::parseOpinions() {

	Opinions opinions;
	tinyxml2::XMLElement *opinion = idea->FirstChildElement("opinion");
	if (opinion != nullptr) {
		while (opinion) {

			Characteristics opCharacs = parseCharacteristics(opinion);
			std::string opText = parseText(opinion);

			Opinion newOpinion(opText, opCharacs);
			opinions.add(newOpinion);

			opinion = opinion->NextSiblingElement("opinion");
		}
	}

	return opinions;
}

IdeaBuilder::~IdeaBuilder()
{
}
