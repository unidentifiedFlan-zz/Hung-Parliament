#include "stdafx.h"
#include "Parliament.h"
#include "PoliticianBuilder.h"
#include "NetworkBuilder.h"
#include "IdeaBuilder.h"
#include "LegislationBuilder.h"
#include <random>

namespace {

	std::vector<double> getRandomVector(const unsigned int &size) {
		std::vector<double> randomList;

		for (unsigned int i = 0; i < size; ++i) {
			randomList.push_back(((double)rand() / RAND_MAX));
		}
		return randomList;
	}
}

Parliament::Parliament(const unsigned int &numMPs, DynamicNetwork *network) : network_(network)
{
	ideas_ = buildIdeas(numMPs);
	nextIdea_ = ideas_.getFirst();
	lastIdea_ = ideas_.getLast();

	MPs_ = buildMPs(numMPs);
	numMPs_ = MPs_.size();

	spawnNewIdeas(MPs_.size()/NUM_POLITICIANS_PER_IDEA);

	//Build network
	NetworkBuilder networkBuilder;
	networkBuilder.build(MPs_, network_);

	//Build legislation
	LegislationBuilder legislationBuilder(characteristicNames_);
	legislation_.push(*legislationBuilder.build(1).getFirst());
}

const Idea Parliament::getNextIdea() {
	if (nextIdea_ == lastIdea_) {
		nextIdea_ = ideas_.getFirst();
		lastIdea_ = ideas_.getLast();
	}
	return *(nextIdea_++);
}

Ideas Parliament::buildIdeas(const unsigned int &numMPs) {

	unsigned int numIdeas = (numMPs > NUM_POLITICIANS_PER_IDEA) ? numMPs / NUM_POLITICIANS_PER_IDEA : 1;
	IdeaBuilder ideaBuilder(characteristicNames_);
	Ideas newIdeas = ideaBuilder.build(numIdeas);

	return newIdeas;
}

std::unordered_map<std::string, Politician> Parliament::buildMPs(const unsigned int &numMPs) {

	std::unordered_map<std::string, Politician> newMPs;

	PoliticianBuilder mpBuilder(this, characteristicNames_);

	for (unsigned int i = 0; i < numMPs; ++i) {
		Politician mp = mpBuilder.build();
		newMPs.emplace(mp.getFirstName() + " " + mp.getLastName(), mp);
	}

	return newMPs;
}


Ideas Parliament::spawnNewIdeas(const unsigned int &numIdeas) {
	// Each MP is assigned a short interval of numbers between 0 and 1.
	// These intervals are summed until the sum is greater than the current 
	// element in a vector of random numbers (in ascending order). The
	// correspondng MP gains the current idea. Since the sum is guaranteed to
	// reach 1 by the time all MPs have been considered, and since the random
	// numbers are between 0 and 1, we guarantee the specified number of ideas
	// -- numIdeas -- are spawned among MPs. The random choice of which MPs
	// gain the ideas are determined by the random numbers generated and the
	// order of MPs which is fixed. The choices are therefore as random as
	// the numbers.

	Ideas spawnedIdeas;

	std::vector<double> randomNums = getRandomVector(numIdeas);
	std::sort(randomNums.begin(), randomNums.end());

	//Step size is interval of numbers allotted to each MP
	double stepSize = 1.0 / numMPs_;

	//Index i represents the ith idea
	unsigned int index = 0;
	//cumulative number is the sum of all intervals up to tha point in the loop
	double cumulNum = 0;

	for (std::unordered_map<std::string, Politician>::iterator it = MPs_.begin();
		 cumulNum <= 1 && it != MPs_.end() && index < ideas_.numberOf(); ++it) {

		if (cumulNum > randomNums[index]) {
			const Idea idea = getNextIdea();
			it->second.addIdea(idea);
			spawnedIdeas.add(idea);
			++index;
		}
		else {
			cumulNum += stepSize;
		}
	}

	return spawnedIdeas;
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

	if (nextMP_ == lastMP_) {

		nextMP_ = MPs_.begin();
		lastMP_ = MPs_.end();
	}

	return &(nextMP_++)->second;
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

	MPIsingModel model;

	double distance = model.calculateMPIdeaDistance(mp, legislation_.top());

	return distance < 6 ? true : false;
}

Parliament::~Parliament()
{
}
