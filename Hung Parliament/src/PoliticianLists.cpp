#include "PoliticianLists.h"

PoliticianLists::PoliticianLists(Network<Politician*, double> *network)
{
	initialiseMostConnectedList(network);
	initialiseMostInfluentialList(network);
}

double PoliticianLists::calculateInfluence(double influence, int numConn) {
	if (numConn == 0) {
		return 0;
	}

	return (influence / numConn);
}

std::vector<PoliticianLists::Connections> PoliticianLists::initialiseMostConnectedList(Network<Politician*, double> *network) {

	for (Network<Politician*, double>::iterator it = network->begin(); it != network->end(); ++it) {

		unsigned int numAdjMPs = it->second.edges.size();
		Connections connections( it->first, numAdjMPs );
		mostConnected_.push_back(connections);
	}

	std::sort(mostConnected_.begin(), mostConnected_.end(), LargestFirst<Connections>());

	return mostConnected_;
}

std::vector<PoliticianLists::Influence> PoliticianLists::initialiseMostInfluentialList(Network<Politician*, double> *network) {

	//Get the sum of weights (influence) across adjacent mps for each mp
	for (Network<Politician*, double>::iterator it = network->begin(); it != network->end(); ++it) {

		double totalInfluence = 0;
		const std::vector<Network<Politician*, double>::Edge> adjMPs = it->second.edges;
		for (std::vector<Network<Politician*, double>::Edge >::const_iterator it2 = adjMPs.begin(); it2 != adjMPs.end(); ++it2) {

			totalInfluence += it2->weight;
		}

		Influence influence(it->first, calculateInfluence(totalInfluence, adjMPs.size()));
		mostInfluential_.push_back(influence);
	}

	std::sort(mostInfluential_.begin(), mostInfluential_.end(), LargestFirst<Influence>());

	return mostInfluential_;
}

std::vector<PoliticianLists::Connections> PoliticianLists::getMostConnectedList() {
	return mostConnected_;
}

std::vector<PoliticianLists::Influence> PoliticianLists::getMostInfluentialList() {
	return mostInfluential_;
}

std::string PoliticianLists::printMostInfluential(int num) {

	std::string mostInfluentialStr;

	std::vector<PoliticianLists::Influence>::iterator it = mostInfluential_.begin();

	for (int i = 1;  i <= num && it != mostInfluential_.end(); ++i, ++it) {
		const Politician* mp = it->politician;
		mostInfluentialStr += "\t" + std::to_string(i) + ") " + mp->getFirstName() + " " + mp->getLastName() + "\n";
	}

	return mostInfluentialStr;
}

std::string PoliticianLists::printMostConnected(int num) {

	std::string mostConnectedStr;

	std::vector<PoliticianLists::Connections>::iterator it = mostConnected_.begin();
	for (int i = 1; i <= num && it != mostConnected_.end(); ++i, ++it) {
		const Politician* mp = it->politician;
		mostConnectedStr += "\t" + std::to_string(i) + ") " + mp->getFirstName() + " " + mp->getLastName() + "\n";
	}

	return mostConnectedStr;
}

PoliticianLists::~PoliticianLists()
{
}
