#include "pch.h"
#include "../Hung Parliament/src/NetworkBuilder.h"
#include "../Hung Parliament/src/CharacteristicsGenerator.h"

class NetworkBuilderTest : public ::testing::Test {

public:

	virtual void SetUp() {
		std::vector<std::string> characNames = { "influence", "socLiberal", "econLiberal" };
		CharacteristicsGenerator characGen(characNames);

		for (int i = 0; i < 100; ++i) {
			Characteristics c = characGen.generateCharacteristics();
			Politician p(std::to_string(i), "", c);
			MPs.add(p);
		}

		NetworkBuilder networkBuilder;
		networkBuilder.build(MPs, &network);

	}

	virtual void TearDown() {

	}

	Network<Politician*, double> network;
	Politicians MPs;
};

TEST_F(NetworkBuilderTest, numAdjNodesTest) {

	int MAX_CONNECTIONS_CONST = 3;
	int min = 1000;
	int max = 0;
	for(Politicians::Iterator it = MPs.getFirst(); it != MPs.getLast(); ++it) {
		Politician *mp = *it;
		int numAdjMPs = network.getAdjacentNodes(mp).size();
		if (numAdjMPs < min) {
			min = numAdjMPs;
		}
		if (numAdjMPs > max) {
			max = numAdjMPs;
		}
	}
	ASSERT_TRUE(min >= 2) << min;
	ASSERT_TRUE(min < 6) << min;
	ASSERT_TRUE(max <= MAX_CONNECTIONS_CONST*sqrt(MPs.numberOf())) << max;
	ASSERT_TRUE(max >= 0.05*MPs.numberOf()) << max;
}