#include "DynamicNetwork.h"


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

void DynamicNetwork::getIdeasFromAdjacentMPs(Politician* randMP, const std::vector<Network<Politician*, double>::Edge> adjMPs) {

	//For each adjacent mp, check their ideas
	for (std::vector<Network<Politician*, double>::Edge>::const_iterator linkIter = adjMPs.begin();
		linkIter != adjMPs.end();
		++linkIter) {
		compareAdjacentIdeas(randMP, *linkIter);
	}
}



void DynamicNetwork::compareAdjacentIdeas(Politician* currentMP, const Network<Politician*, double>::Edge adjMP) {

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

		double randomDouble = getRandomDouble();

		if (model_.ideaDiffusionProbability(currentMP, *ideaIter, adjMP.weight) > randomDouble) {
			currentMP->replaceWeakestIdea(*ideaIter);
		}
	}

}

Politician* DynamicNetwork::getRandomNode() {
	// Probabilities proportional to number of links.
	// Store total number of links. Prob. per link = 1.0/totalNumLinks.
	// Prob. of gettingNode = numNodeLinks*Prob per link. 

	double randDouble = getRandomDouble();
	double sum = 0;
	double step = 1 / Network<Politician*, double>::NUM_LINKS;
	for (typename Network<Politician*, double>::iterator it = Network<Politician*, double>::network_.begin();
		  it != Network<Politician*, double>::network_.end(); ++it) {

		sum += ((double)it->second.edges.size())*step;
		if (randDouble < sum) {
			return it->first;
		}
	}

	return Network<Politician*, double>::network_.begin()->first;
}