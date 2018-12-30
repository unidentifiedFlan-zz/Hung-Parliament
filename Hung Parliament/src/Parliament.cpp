#include "stdafx.h"
#include "Parliament.h"
#include "PoliticianBuilder.h"
#include "NetworkBuilder.h"
#include "IdeaBuilder.h"
#include "LegislationBuilder.h"
#include <random>


Parliament::Parliament(int numMPs, AbstractNetworkDynamics<Politician*, double> *network) : network_(network)
{
	//Build ideas
	int numIdeas = (numMPs > 5) ? numMPs / 5 : 1;
	IdeaBuilder ideaBuilder(characteristicNames_);
	ideas_ = ideaBuilder.build(numIdeas);

	//Build MPs
	PoliticianBuilder mpBuilder(this, characteristicNames_);

	for (int i = 0; i < numMPs; ++i) {
		Politician mp = mpBuilder.build();
		MPs_.emplace(mp.getFirstName() + " " + mp.getLastName(), mp);
	}
	numMPs_ = MPs_.size();

	//distribute ideas
	unsigned int j = 0;
	for (std::unordered_map<std::string, Politician>::iterator it = MPs_.begin(); it != MPs_.end() && j < ideas_.size(); ++it) {

		if (it == MPs_.begin()) {
			it->second.addIdea(&ideas_[0]);
			++j;
		}
		else if (((double)rand() / RAND_MAX) < 0.1) {
			it->second.addIdea(&ideas_[j]);
			++j;
		}
	}

	//Build network
	NetworkBuilder networkBuilder;
	networkBuilder.build(MPs_, network_);

	//Build legislation
	LegislationBuilder legislationBuilder(characteristicNames_);
	legislation_.push(legislationBuilder.build(1).front());
}

void Parliament::handleEvent(Event &e) {
	notifyListeners(e);
}

Politician* Parliament::findMP(std::string mp) {

	std::unordered_map<std::string, Politician>::iterator it = MPs_.find(mp);
	if (it == MPs_.end()) {
		return nullptr;
	}

	return &(it->second);
}

std::vector<Network<Politician*, double>::Edge> Parliament::getMPConnections(Politician* mp) const {
	return network_->getAdjacentNodes(mp);
}

Politician* Parliament::getNextMP() {

	if (MPIter == MPs_.end()) {
		MPIter = MPs_.begin();
	}

	return &(MPIter++)->second;
}

int Parliament::getNumberOfMPs() {
	return numMPs_;
}

PoliticianLists Parliament::createPoliticianLists() {
	PoliticianLists lists(network_);

	return lists;
}

Idea Parliament::getLegislation() {
	return legislation_.top();
}

bool Parliament::calculateMPSupport(Politician *mp) const {

	double distance = mp->calculateIdeaDistance(&(legislation_.top()));

	return distance < 6 ? true : false;
}

Parliament::~Parliament()
{
}
