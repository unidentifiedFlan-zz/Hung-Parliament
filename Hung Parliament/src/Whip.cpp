#include "stdafx.h"
#include "Whip.h"


Whip::Whip(Parliament *parliament, PoliticianLists &lists) : parliament_(parliament), lists_(lists) {

	calculateTotalLegislationSupport();
}

int Whip::calculateTotalLegislationSupport() {

	for (int i = 0; i < parliament_->getNumberOfMPs(); ++i) {

		Politician *mp = parliament_->getNextMP();

		numMPsSupportingLegislation_ += parliament_->calculateMPSupport(mp);
	}

	return numMPsSupportingLegislation_;
}

void Whip::handleEvent(Event &e) {

	std::string output = e.politician->getName();

	if (e.type == Event::addedIdea) {
		output += " has adopted the idea " + e.idea.getName();
	}
	else {
		output += " has dropped the idea " + e.idea.getName();
	}

	Output::whipEvent(output);

	output += updateLegislationSupport(e.politician);
}

std::string Whip::updateLegislationSupport(Politician* mp) {

	bool  currentSupport = parliament_->calculateMPSupport(mp);
	if (currentSupport == support_[mp]) {
		return "";
	}
	support_[mp] = currentSupport;

	std::string output = mp->getName();
	if (currentSupport) {
		output += " now supports the legislation.";
		numMPsSupportingLegislation_++;
	}
	else {
		output += " no longer supports the legislation.";
		numMPsSupportingLegislation_--;
	}

	Output::whipEvent(output);

	return output;
}

std::string Whip::getAdvice() {
	//Fairly straightforward such as "These MPs are against and are the most connected. Ted Howard is a connection
	//and he's looking fairly persuadable"

	std::string advice = "You should primarily target the most charismatic and well-connected MPs.";

	advice += " The most influential are:\n";
	advice += lists_.printMostInfluential(10);

	advice += "and the most well-connected are:\n";
	advice += lists_.printMostConnected(10);

	return advice;
}

std::string Whip::getStatistics() {
	int req = 0.5*parliament_->getNumberOfMPs();

	std::string stats = "There are " + std::to_string(parliament_->getNumberOfMPs()) + " MPs in parliament.";
	stats += " Currently " + std::to_string(numMPsSupportingLegislation_) +
			(numMPsSupportingLegislation_ == 1 ? " MP supports" : " MPs support") + " the legislation. We need " + 
		     std::to_string(req) + " MPs to pass the vote.";
	return stats;
}

std::string Whip::getTimeRemaining() {
	return "";
}

std::string Whip::describeLegislation() {

	Idea legislation = parliament_->getLegislation();
	return "The legislation currently being proposed is " + legislation.getName() +
		   ". It's purpose is as follows: " + legislation.getDescription();
}

Idea Whip::getLegislation() {
	return parliament_->getLegislation();
}

Politician* Whip::findMP(std::string &mp) {
	return parliament_->findMP(mp);
}

std::string Whip::getMPDetails(const Politician* mp) {
	std::string details = mp->getName() + " has the following characteristics:\n";

	Characteristics characs = mp->getCharacteristics();
	details += getCharacteristicDetails(characs);

	return details;
}

std::string Whip::getIdeaDetails(const Idea &idea) {
	std::string details = idea.getName() + " has the following characteristics:\n";
	
	Characteristics characs = idea.getCharacteristics();
	details += getCharacteristicDetails(characs);

	return details;
}

std::string Whip::getCharacteristicDetails(Characteristics &characs) {

	std::string details;

	std::vector<Characteristics::Characteristic> characList = characs.getList();

	for (std::vector<Characteristics::Characteristic>::iterator it = characList.begin(); it != characList.end(); ++it) {
		details += it->name + ":\t" + std::to_string(it->value) + "\n";
	}

	return details;
}


Whip::~Whip()
{
}
