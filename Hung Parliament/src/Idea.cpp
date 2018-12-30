#include "stdafx.h"
#include "Idea.h"


Idea::Idea(std::string name, std::string descrip, Characteristics characs, std::vector<Opinion> opinions) : 
	              name_(name), description_(descrip), characteristics_(characs), opinions_(opinions) {}

Idea::Idea(std::string name, std::string descrip, Characteristics characs) :
		name_(name), description_(descrip), characteristics_(characs) {}

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

const std::vector<Opinion> Idea::getOpinions() const {
	return opinions_;
}

void Idea::addOpinion(Opinion op) {
	opinions_.push_back(op);
}

Idea::~Idea()
{
}
