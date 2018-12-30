#include "pch.h"
#include "../Hung Parliament/src/AbstractNetworkDynamics.h"

class AbstractNetworkDynamicsTest : public ::testing::Test {

public:

	class object {
		int _ref;
	public:
		object(int newRef) : _ref(newRef) {}
		int getRef() { return _ref; }
		void setRef(int val) { _ref = val; }
	};

	virtual void SetUp() {

		for (int num = 0; num != 300; ++num) {
			object* o = new object(num);
			objectList.emplace( o, 0 );
			++listSize;
			_network.addNode(o);
		}

		srand(static_cast<unsigned int>(time(NULL)));

		for (std::map<object*, int>::iterator it1 = objectList.begin(); it1 != objectList.end(); ++it1) {

			for (std::map<object*, int>::iterator it2 = (++it1); it2 != objectList.end(); ++it2) {

				if ((((double)rand()) / RAND_MAX) < 0.25) {
					object * o1 = it1->first;
					object * o2 = it2->first;
					_network.addLink(o1, o2, (it2->first->getRef() - it1->first->getRef()));
					++numLinks;
				}
			}
		}
	}

	virtual void TearDown() {
		for (std::map<object*, int>::iterator it = objectList.begin(); it != objectList.end(); ++it) {
			delete it->first;
		}
	}

	AbstractNetworkDynamics<object*, int> _network;
	std::map<object*, int> objectList;
	int listSize = 0;
	int numLinks = 0;
};

TEST_F(AbstractNetworkDynamicsTest, randomNodeTest) {

	int numTests = 10000;

	for (int i = 0; i < numTests; ++i) {
		object* obj = _network.getRandomNode();

		//Having chosen a random node, we find its place in the node list and increment its counter
		for (std::map<object*, int>::iterator it = objectList.begin(); it != objectList.end(); ++it) {
			if (obj == it->first) {
				++(it->second);
				break;
			}
		}
	}

	for (Network<object*, int>::iterator netIt = _network.begin(); netIt != _network.end(); ++netIt) {
		for (std::map<object*, int>::iterator listIt = objectList.begin(); listIt != objectList.end(); ++listIt) {

			if (netIt->first == listIt->first) {
				//Probability of selecting a node is proportional to the number of links it has in the network.
				//The expected number of times a node will be chosen is therefore proportional to the the number of links
				//it has as a proportion of the total number of links
				double expectation = numTests * (((double)netIt->second.edges.size()) / numLinks);

				EXPECT_NEAR(expectation, listIt->second, 0.25*expectation) 
					<< "num adj nodes: "
					<< netIt->second.edges.size() << " numLinks: " << numLinks << " object no: " << listIt->first->getRef()
					<< " linkSensitivity: " << ((double)listIt->second / netIt->second.edges.size());
				break;
			}
		}
	}
}