#include "pch.h"
#include "../Hung Parliament/src/Network.h"
#include "../Hung Parliament/src/PoliticianLists.h"
#include "../Hung Parliament/src/Characteristics.h"


class PoliticianListsTest : public ::testing::Test {

public:

	virtual void SetUp() {
		std::vector<Characteristics::Characteristic> vec;
		Characteristics characs(vec);

		int numMPs = 10;

		for (int i = 0; i < numMPs; ++i) {
			Politician *p = new Politician(std::to_string(i), "", characs);
			pols.push_back(p);
			network.addNode(pols[i]);

			for (int j = 0; j < i; ++j) {
				network.addLink(pols[i], pols[j], numMPs - i);
			}
		}

		lists = new PoliticianLists(&network);
	}

	virtual void TearDown() {
		delete lists;
		for (std::vector<Politician*>::iterator it = pols.begin(); it != pols.end(); ++it) {
			delete *it;
		}
	}

	Network<Politician*, double> network;
	std::vector<Politician*> pols;
	PoliticianLists *lists;
};

//Politicians should be ordered by number of links. The number of links inreases with i
TEST_F(PoliticianListsTest, GetMostConnectedTest) {

	std::vector<PoliticianLists::Connections> list = lists->getMostConnectedList();

	int i = list.size() - 1;
	for (std::vector<PoliticianLists::Connections>::iterator it = list.begin(); it != list.end(); ++it, --i) {
		ASSERT_EQ(std::to_string(i), it->politician->getFirstName());
	}
}

//The list should return the politicians with the greatest average influence
TEST_F(PoliticianListsTest, GetMostInfluentialTest) {

	std::vector<PoliticianLists::Influence> influenceList = lists->getMostInfluentialList();

	std::vector<PoliticianLists::Influence>::iterator it2 = influenceList.begin()++;
	for (std::vector<PoliticianLists::Influence>::iterator it1 = influenceList.begin(); it2 != influenceList.end(); ++it1, ++it2) {
		ASSERT_TRUE(it2->value >= it1->value);
	}
}