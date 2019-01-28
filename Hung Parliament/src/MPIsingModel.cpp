/* 
------MP ISING model--------

The model works by first selecting a random node, representing a politician, in the network. The adjacent nodes,
representing the politician's social network, are obtained and their ideas inspected. The probability the
politician adopts a particular idea is determined by how similar the ideology of the politician and their
currently held ideas are to that of the idea's. The chance of adopting an idea is increased by some additional
factor determined by how many politicians in that social circle also hold that idea this information is stored in 
_exploredIdeas.
The effect is radical ideas should remain marginal but have a small probability of gaining traction. More centrist
ideas should dominate.

*/

#include "stdafx.h"
#include "MPIsingModel.h"

MPIsingModel::MPIsingModel() { lastMPObserved = nullptr; }

MPIsingModel::MPIsingModel(double alpha, double beta, double ideaInfluence) : alpha_(alpha), beta_(beta), IDEA_INFLUENCE(ideaInfluence)
{
	lastMPObserved = nullptr;
}

double MPIsingModel::ideaDiffusionProbability(Politician* mp, const Idea &idea, double externalInfluence) {

	double probability = 0;
	
	// This is the joint affinity between the MP and their current ideas with the idea being considered 
	// for adoption
	double MPIdeaDistance = calculateMPIdeaDistance(mp, idea);
	
	double totalExternalInfluence = getTotalExternalInfluence(mp, idea);

	double H = alpha_*(MPIdeaDistance) - totalExternalInfluence;

	probability = exp(-beta_*H);

	return probability;
}

double MPIsingModel::getTotalExternalInfluence(Politician* mp, const Idea &idea) {

	// ExploredIdeas is used to store the ideas already explored in this round of idea propagation. Each
	// time the same idea is considered for adoption, it's probability increases.
	// We will refresh exploredIdeas each time we switch to a new mp so only the effect is only short term.
	// This ensures the effect is dependent on the pressure being exerted at a particular time rather than
	// a slow drip toward inevitability
	if (mp != lastMPObserved) {
		exploredIdeas_.clear();
	}
	double externalInfluence = (exploredIdeas_.exists(idea) ? exploredIdeas_.find(idea)->second : 0);
	updateTotalExternalInfluence(idea, externalInfluence);

	return externalInfluence;

}
double MPIsingModel::updateTotalExternalInfluence(const Idea &idea, double influence) {

	if (exploredIdeas_.exists(idea)) {
		exploredIdeas_.update(idea, influence + exploredIdeas_.find(idea)->second);
	}
	else {
		exploredIdeas_.add(idea, influence);
	}

	return exploredIdeas_.find(idea)->second;
}
// The sum of the characteristic differences between the idea
// being considered and those held by the politician
double MPIsingModel::ideaIdeaDistance(Politician* mp, const Idea &idea) {

	double ideaIdeaDistance = 0;

	Ideas::Iterator ideasIter = mp->getIdeas().getFirst();

	ideasIter != mp->getIdeas().getLast();

	for (Ideas::Iterator ideasIter = mp->getIdeas().getFirst();
		ideasIter != mp->getIdeas().getLast();
		++ideasIter) {

		double distance = idea.getCharacteristics().characteristicDistance(ideasIter->getCharacteristics());

		ideaIdeaDistance += distance;
	}

	return ideaIdeaDistance;
}

double MPIsingModel::calculateMPIdeaDistance(Politician *mp, const Idea &idea) {

	double MPIdeaDistance = idea.getCharacteristics().characteristicDistance(mp->getCharacteristics());

	double ideasIdeaDistance = ideaIdeaDistance(mp, idea);
	
	return abs(MPIdeaDistance) + IDEA_INFLUENCE*abs(ideasIdeaDistance);
}

MPIsingModel::~MPIsingModel()
{
}