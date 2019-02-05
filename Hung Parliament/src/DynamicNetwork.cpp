#include "DynamicNetwork.h"
#include "RandomGenerator.h"


DynamicNetwork::DynamicNetwork(int interval, const MPIsingModel &model) : runInterval_(interval), model_(model)  {}

void DynamicNetwork::runDynamics(bool *quit) {

	while (!(*quit)) {

		//Select a politician for adopting neighbouring ideas at the end of every run interval
		time_t now = time(0);
		if (difftime(now, lastRunTime_) > runInterval_) {
			Politician* randMP = getRandomNode();

			//Check Mp exists in the network and is not currently having its data altered elsewhere
			while (!(randMP && nodeValid(randMP) && randMP->isAvailable())) {
				randMP = getRandomNode();
			}

			getIdeasFromAdjacentMPs(randMP, getAdjacentNodes(randMP));
			randMP->setAvailable();

			lastRunTime_ = now;
		}
	}
}

void DynamicNetwork::getIdeasFromAdjacentMPs(Politician* randMP, const std::vector<Edge> adjMPs) {

	//For each adjacent mp, check their ideas
	for (std::vector<Edge>::const_iterator linkIter = adjMPs.begin();
		linkIter != adjMPs.end();
		++linkIter) {
		compareAdjacentIdeas(randMP, *linkIter);
	}
}



void DynamicNetwork::compareAdjacentIdeas(Politician* currentMP, const Edge adjMP) {

	// For each idea held by an adjacent MP, calculate the probability of adoption and, if sufficiently great, add 
	// it to the MP's list of ideas. If the list is full, check whether the MP's weakest idea -- that is the currently
	// held idea they have least affinity for -- can be replaced (i.e the new idea has a higher affinity with this MP than
	// the weakest idea) .
	for (Ideas::Iterator ideaIter = adjMP.adjacentNode->get->getIdeas().getFirst();
		ideaIter != adjMP.adjacentNode->get->getIdeas().getLast();
		++ideaIter) {

		if (currentMP->hasIdea(*ideaIter)) {
			continue;
		}

		RandomGenerator *gen = RandomGenerator::getInstance();
		double randomDouble = gen->generateDouble();

		if (model_.ideaDiffusionProbability(currentMP, *ideaIter, adjMP.weight) > randomDouble) {
			currentMP->replaceWeakestIdea(*ideaIter);
		}
	}

}

Politician* DynamicNetwork::getRandomNode() {
	// Probabilities proportional to number of links.
	// Store total number of links. Prob. per link = 1.0/totalNumLinks.
	// Prob. of gettingNode = numNodeLinks*Prob per link. 

	int numLinks = NUM_LINKS;

	//Prevent division by zero and make each Politician equally probable
	if (numLinks == 0) {
		numLinks = network_.size();
	}
	double step = 1.0/numLinks;

	RandomGenerator *gen = RandomGenerator::getInstance();
	double randomDouble = gen->generateDouble();

	double sum = 0;
	for (typename iterator it = network_.begin();
		  it != network_.end(); ++it) {

		double numAdjMPs = it->second.edges.size();
		if (NUM_LINKS == 0) {
			numAdjMPs = 1;
		}
		sum += numAdjMPs*step;
		if (randomDouble < sum) {
			return it->first;
		}
	}

	return network_.begin()->first;
}