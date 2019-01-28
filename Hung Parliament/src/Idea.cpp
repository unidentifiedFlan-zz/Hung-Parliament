#include "stdafx.h"
#include "Idea.h"
#include "RandomGenerator.h"


Idea::Idea(std::string name, std::string descrip, Characteristics characs, Opinions opinions) : 
	              id_(generateID()), name_(name), description_(descrip), characteristics_(characs), opinions_(opinions) {}

Idea::Idea(std::string name, std::string descrip, Characteristics characs) :
		id_(generateID()), name_(name), description_(descrip), characteristics_(characs) {}

const unsigned int Idea::generateID() {

	RandomGenerator *generator = RandomGenerator::getInstance();

	return generator->generate();
}

const std::string Idea::getName() const {
	return name_;
}

const std::string Idea::getDescription() const {
	return description_;
}

const int Idea::getInfluence() const {
	return influence_;
}
const Characteristics Idea::getCharacteristics() const {
	return characteristics_;
}

const Opinions Idea::getOpinions() const {
	return opinions_;
}

void Idea::addOpinion(Opinion opinion) {
	opinions_.add(opinion);
}

void Idea::removeOpinion(Opinion opinion) {
	opinions_.remove(opinion);
}

Idea::~Idea()
{}
