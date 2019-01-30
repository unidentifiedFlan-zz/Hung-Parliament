#include "pch.h"
#include "../Hung Parliament/src/DynamicNetwork.h"
#include "../Hung Parliament/src/RandomGenerator.h"

class DynamicNetworkTest : public ::testing::Test {

	void addNodesToNetwork() {
		Characteristics characs;
		for (int num = 0; num != 300; ++num) {
			Politician* p = new Politician(std::to_string(num), "", characs);
			politicians.emplace(p, 0);
			_network->addNode(p);
		}
	}

	void addLinksToNetwork() {

		RandomGenerator *generator = RandomGenerator::getInstance();

		for (std::map<Politician*, int>::iterator it1 = politicians.begin(); it1 != politicians.end(); ++it1) {

			//The second iterator is one ahead of the first iterator
			for (std::map<Politician*, int>::iterator it2 = politicians.begin(); it2 != politicians.end(); ++it2) {

				if (it1 == it2) {
					continue;
				}

				double randDouble = generator->generateDouble();

				if (randDouble < 0.05) {
					Politician * p1 = it1->first;
					Politician * p2 = it2->first;
					_network->addLink(p1, p2, 1);
					++numLinks;
				}
			}
		}
	}

	void buildNetwork() {

		addNodesToNetwork();

		addLinksToNetwork();
	}
public:

	virtual void SetUp() {

		MPIsingModel model;
		_network = new DynamicNetwork(10000, model);

		buildNetwork();
	}

	virtual void TearDown() {
		for (std::map<Politician*, int>::iterator it = politicians.begin(); it != politicians.end(); ++it) {
			delete it->first;
		}

		delete _network;
	}

	DynamicNetwork *_network;
	std::map<Politician*, int> politicians;
	int numLinks = 0;
};

TEST_F(DynamicNetworkTest, randomNodeTest) {

	int numTests = 10000;

	for (int i = 0; i < numTests; ++i) {
		Politician* randPolitician = _network->getRandomNode();

		//Having chosen a random node, we find its place in the node list and increment its counter
		std::map<Politician*, int>::iterator it = politicians.find(randPolitician);
		if (it != politicians.end()) {
			++(it->second);
		}
	}

	double frequencyRatio = 0;

	for (DynamicNetwork::iterator netIt = _network->begin(); netIt != _network->end(); ++netIt) {

		std::map<Politician*, int>::iterator MPIt = politicians.find(netIt->first);
		if (MPIt != politicians.end()) {
			//Probability of selecting a node is proportional to the number of links it has in the network.
			//The expected number of times a node will be chosen is therefore proportional to the the number of links
			//it has as a proportion of the total number of links
			double expectation = numTests * (((double)netIt->second.edges.size()) / numLinks);

			if (expectation > 0) {
				frequencyRatio += (double)MPIt->second / expectation;
			}
		}
	}

	double averageFrequencyRatio = frequencyRatio / politicians.size();
	EXPECT_NEAR(1.0, averageFrequencyRatio, 0.1);
}