#include "NetworkBuilder.h"

NetworkBuilder::NetworkBuilder()
{
	srand(static_cast<unsigned int>(time(0)));
}

Network<Politician*, double>* NetworkBuilder::build(Politicians &MPs,
	                                                Network<Politician*, double> *network) {

	network_ = network;

	for (Politicians::Iterator it = MPs.getFirst(); it != MPs.getLast(); ++it) {
		Politician * mp = *it;
		network->addNode(mp);
		buildLinks(mp, MPs);
	}

	return network_;
}

Network<Politician*, double>* NetworkBuilder::buildLinks(Politician *mp, Politicians &MPs) {

	for (Politicians::Iterator it2 = MPs.getFirst(); it2 != MPs.getLast(); ++it2) {
		Politician * mp2 = *it2;

		RandomGenerator *generator = RandomGenerator::getInstance();
		double randNum = generator->generateDouble();

		if (!(mp == mp2) && !linkExists(mp, mp2) && (addProbability(mp, mp2) > randNum)) {

			network_->addLink(mp, mp2, 5);
			network_->addLink(mp2, mp, 5);
		}
	}

	return network_;
}

const bool NetworkBuilder::linkExists(Politician *mp1, Politician *mp2) {
	std::vector<Network<Politician*, double>::Edge> adjNodes = network_->getAdjacentNodes(mp1);

	for (std::vector<Network<Politician*, double>::Edge>::iterator it = adjNodes.begin(); it != adjNodes.end(); ++it) {
		if (it->adjacentNode->get == mp2) {
			return true;
		}
	}

	return false;
}

const double NetworkBuilder::addProbability(Politician *mp1, Politician *mp2) {
	// Each additional link becomes more improbable. The probability of a new link
	// is inversely proportional to the number of links it already has.

	double characsDist = mp1->getCharacteristics().characteristicDistance(mp2->getCharacteristics());

	if (characsDist < 0.1) {
		return 1;
	}

	int numAdjNodes = network_->getAdjacentNodes(mp1).size();

	// Prevent a singularity
	if (numAdjNodes < 1) {
		numAdjNodes = 1;
	}

	return 1 / (characsDist*pow(numAdjNodes,2));
}

NetworkBuilder::~NetworkBuilder()
{
}
