#include "pch.h"
#include "../Hung Parliament/src/MPIsingModel.h"


class MPIsingTest : public ::testing::Test {

public:
	virtual void SetUp() {
		_model = new MPIsingModel(10000);
		Characteristics::Characteristic socLiberal("socLiberal", -5);
		Characteristics::Characteristic econLiberal("econLiberal", -5);
		Characteristics::Characteristic enviroProgressive("enviroProgressive", -5);
		Characteristics characsA({socLiberal, econLiberal, enviroProgressive});

		ideaA = new Idea("ideaA", "ideaA", characsA);

		socLiberal.value = 0;
		econLiberal.value = 0;
		enviroProgressive.value = 0;
		Characteristics characsB({ socLiberal, econLiberal, enviroProgressive });

		ideaB = new Idea("ideaB", "ideaB", characsB);

		socLiberal.value = 5;
		econLiberal.value = 5;
		enviroProgressive.value = 5;
		Characteristics characsC({ socLiberal, econLiberal, enviroProgressive });

		ideaC = new Idea("ideaC", "ideaC", characsC);

		socLiberal.value = -5;
		econLiberal.value = -5;
		enviroProgressive.value = -5;
		Characteristics characsD({ socLiberal, econLiberal, enviroProgressive });

		mp = new Politician("John", "Smith", characsD);
	}

	virtual void TearDown() {
		delete ideaA;
		delete ideaB;
		delete ideaC;
		delete mp;
	}

	MPIsingModel* _model;
	Politician* mp;
	Idea* ideaA, *ideaB, *ideaC;
};


TEST_F(MPIsingTest, ideaDiffusionProbabilityTest) {

	ASSERT_EQ(1, _model->ideaDiffusionProbability(mp,ideaA));
	EXPECT_NEAR(0.2, _model->ideaDiffusionProbability(mp, ideaB), 0.1);
	EXPECT_NEAR(0, _model->ideaDiffusionProbability(mp, ideaC), 0.05);
}