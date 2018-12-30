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

	//Using windows.h
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO buffInfo;

	GetConsoleScreenBufferInfo(handle, &buffInfo);
	WORD origAttr = buffInfo.wAttributes;
	SetConsoleTextAttribute(handle, 4);

	std::cout << "\rWhip: " + e.politician->getFirstName() + " " + e.politician->getLastName();

	if (e.type == Event::addedIdea) {
		std::cout << " has adopted the idea " + e.idea->getName() << std::endl;
	}
	else {
		std::cout << " has dropped the idea " + e.idea->getName() << std::endl;
	}

	updateLegislationSupport(e.politician);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), origAttr);
	std::cout << "\rCommand: ";
}

void Whip::updateLegislationSupport(Politician* mp) {

	bool  currentSupport = parliament_->calculateMPSupport(mp);
	if (currentSupport == support_[mp]) {
		return;
	}
	support_[mp] = currentSupport;

	std::cout << "\rWhip: " + mp->getFirstName() + " " + mp->getLastName();
	if (currentSupport) {
		std::cout << " now supports the legislation." << std::endl;
		numMPsSupportingLegislation_++;
	}
	else {
		std::cout << " no longer supports the legislation." << std::endl;
		numMPsSupportingLegislation_--;
	}
}

std::string Whip::getAdvice() {
	//Fairly straightforward such as "These MPs are against and are the most connected. Ted Howard is a connection
	//and he's looking fairly persuadable"

	std::string advice = "Whip: You should primarily target the most charismatic and well-connected MPs.";

	advice += " The most influential are:\n";
	advice += lists_.printMostInfluential(10);

	advice += "and the most well-connected are:\n";
	advice += lists_.printMostConnected(10);

	return advice;
}

std::string Whip::getStatistics() {
	int req = 0.5*parliament_->getNumberOfMPs();

	std::string stats = "Whip: There are " + std::to_string(parliament_->getNumberOfMPs()) + " MPs in parliament.";
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
	return "Whip: The legislation currently being proposed is " + legislation.getName() +
		   ". It's purpose is as follows: " + legislation.getDescription();
}

Idea Whip::getLegislation() {
	return parliament_->getLegislation();
}

Politician* Whip::findMP(std::string &mp) {
	return parliament_->findMP(mp);
}

Whip::~Whip()
{
}
