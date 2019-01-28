#include "pch.h"
#include "../Hung Parliament/src/DynamicNetwork.h"

class DynamicNetworkTest : public ::testing::Test {

public:

	virtual void SetUp() {

		MPIsingModel model;
		_network = new DynamicNetwork(10000, model);
		Characteristics characs;
		for (int num = 0; num != 300; ++num) {
			Politician* p = new Politician(std::to_string(num), "", characs);
			politicians.emplace(p, 0);
			++listSize;
			_network->addNode(p);
		}

		srand(static_cast<unsigned int>(time(NULL)));

		for (std::map<Politician*, int>::iterator it1 = politicians.begin(); it1 != politicians.end(); ++it1) {

			for (std::map<Politician*, int>::iterator it2 = (++it1); it2 != politicians.end(); ++it2) {

				if ((((double)rand()) / RAND_MAX) < 0.25) {
					Politician * p1 = it1->first;
					Politician * p2 = it2->first;
					_network->addLink(p1, p2, 1);
					++numLinks;
				}
			}
		}
	}

	virtual void TearDown() {
		for (std::map<Politician*, int>::iterator it = politicians.begin(); it != politicians.end(); ++it) {
			delete it->first;
		}

		delete _network;
	}

	DynamicNetwork *_network;
	std::map<Politician*, int> politicians;
	int listSize = 0;
	int numLinks = 0;
};

TEST_F(DynamicNetworkTest, randomNodeTest) {

	int numTests = 10000;

	for (int i = 0; i < numTests; ++i) {
		Politician* randPolitician = _network->getRandomNode();

		//Having chosen a random node, we find its place in the node list and increment its counter
		for (std::map<Politician*, int>::iterator it = politicians.begin(); it != politicians.end(); ++it) {
			if (randPolitician == it->first) {
				++(it->second);
				break;
			}
		}
	}

	for (DynamicNetwork::iterator netIt = _network->begin(); netIt != _network->end(); ++netIt) {
		for (std::map<Politician*, int>::iterator listIt = politicians.begin(); listIt != politicians.end(); ++listIt) {

			if (netIt->first == listIt->first) {
				//Probability of selecting a node is proportional to the number of links it has in the network.
				//The expected number of times a node will be chosen is therefore proportional to the the number of links
				//it has as a proportion of the total number of links
				double expectation = numTests * (((double)netIt->second.edges.size()) / numLinks);

				EXPECT_NEAR(expectation, listIt->second, 0.25*expectation) 
					<< "num adj nodes: "
					<< netIt->second.edges.size() << " numLinks: " << numLinks << " politician no: " << listIt->first->getFirstName()
					<< " linkSensitivity: " << ((double)listIt->second / netIt->second.edges.size());
				break;
			}
		}
	}
}