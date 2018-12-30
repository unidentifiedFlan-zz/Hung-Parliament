#include "IdeaBuilder.h"

IdeaBuilder::IdeaBuilder(std::vector<std::string> &characNames) : characteristicNames(characNames){}

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

std::vector<Idea> IdeaBuilder::build(int numIdeas) {

	std::vector<Idea> ideaVector;

	if (idea == nullptr && !initParser()) {
		return ideaVector;
	}

	for (int n = 0; idea && n < numIdeas; ++n) {

		std::string ideaName = parseIdeaName();
		std::string ideaDescription = parseText(idea);
		Characteristics ideaCharacs = parseCharacteristics(idea);

		std::vector<Opinion> opinionVector = parseOpinions();

		//Create idea
		Idea newIdea(ideaName, ideaDescription, ideaCharacs, opinionVector);
		ideaVector.push_back(newIdea);
		
		idea = idea->NextSiblingElement("idea");
	}

	ideas.insert(ideas.end(), ideaVector.begin(), ideaVector.end());

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

std::vector<Opinion> IdeaBuilder::parseOpinions() {

	std::vector<Opinion> opinionVector;
	tinyxml2::XMLElement *opinion = idea->FirstChildElement("opinion");
	if (opinion != nullptr) {
		while (opinion) {

			Characteristics opCharacs = parseCharacteristics(opinion);
			std::string opText = parseText(opinion);

			Opinion newOpinion(opText, opCharacs);
			opinionVector.push_back(newOpinion);

			opinion = opinion->NextSiblingElement("opinion");
		}
	}

	return opinionVector;
}


IdeaBuilder::~IdeaBuilder()
{
}
