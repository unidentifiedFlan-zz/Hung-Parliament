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


MPIsingModel::MPIsingModel(int interval) : AbstractNetworkDynamics(), _runInterval(interval)
{
}

void MPIsingModel::runDynamics(bool *quit) {

	while (!(*quit)) {

		//Select a politician for adopting neighbouring ideas at the end of every run interval
		time_t now = time(0);
		if (difftime(now, _lastRunTime) > _runInterval) {
			Politician* randMP = getRandomNode();

			//Check Mp exists in the network and is not currently having its data altered elsewhere
			while(!(randMP && nodeValid(randMP) && randMP->isAvailable())) {
				randMP = getRandomNode();
			}

			getIdeasFromAdjacentMPs(randMP, getAdjacentNodes(randMP));
			randMP->setAvailable();

			_lastRunTime = now;
		}
	}
}

void MPIsingModel::getIdeasFromAdjacentMPs(Politician* randMP, const std::vector<Network<Politician*, double>::Edge> adjMPs) {

	_exploredIdeas.clear();

	//For each adjacent mp, check their ideas
	for (std::vector<Network<Politician*, double>::Edge>::const_iterator linkIter = adjMPs.begin();
		linkIter != adjMPs.end();
		++linkIter) {

		compareAdjacentIdeas(randMP, *linkIter);
	}
}



void MPIsingModel::compareAdjacentIdeas(Politician* currentMP, const Network<Politician*, double>::Edge adjMP) {

	// For each idea held by an adjacent MP, calculate the probability of adoption and, if sufficiently great, add 
	// it to the MP's list of ideas. If the list is full, check whether the MP's weakest idea -- that is the currently
	// held idea they have least affinity for -- can be replaced (i.e the new idea has a higher affinity with this MP than
	// the weakest idea) .
	for (std::vector<const Idea*>::const_iterator ideaIter = adjMP.adjacentNode->get->getListOfIdeas().begin();
		ideaIter != adjMP.adjacentNode->get->getListOfIdeas().end();
		++ideaIter) {

		if (currentMP->hasIdea(*ideaIter)) {
			continue;
		}

		double randomDouble = getRandomDouble();

		if (ideaDiffusionProbability(currentMP, *ideaIter) > randomDouble) {
			currentMP->replaceWeakestIdea(*ideaIter);
		}


		if (_exploredIdeas.exists(*ideaIter)){
			_exploredIdeas.update(*ideaIter, adjMP.weight + _exploredIdeas.find(*ideaIter)->second);
		}
		else {
			_exploredIdeas.add(*ideaIter, adjMP.weight);
		}
	}

}

double MPIsingModel::ideaDiffusionProbability(Politician* currentMP, const Idea* idea) {

	double probability = 0;

	// Parameters to be calibrated
	double alpha = 1.1, beta = 0.1;

	// This is the joint affinity between the MP and their current ideas with the idea being considered 
	// for adoption
	double MPIdeaDistance = currentMP->calculateIdeaDistance(idea);

	// _exploredIdeas is used to store the ideas already explored in this round of idea propagation. Each
	// time the same idea is considered for adoption, it's probability increases.
	double cumulativeInfluence = (_exploredIdeas.exists(idea) ? _exploredIdeas.find(idea)->second : 0);

	double H = alpha*(MPIdeaDistance) - cumulativeInfluence;

	probability = exp(-beta*H);

	return probability;
}


MPIsingModel::~MPIsingModel()
{
}
