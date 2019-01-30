#include "pch.h"
#include "../Hung Parliament/src/MPIsingModel.h"

class MPIsingTest : public ::testing::Test {

public:
	virtual void SetUp() {
		model = new MPIsingModel();

		ideaA = new Idea(createIdea("A", -5, -5, -5));
		ideaB = new Idea(createIdea("B", 0, 0, 0));
		ideaC = new Idea(createIdea("C", 5, 5, 5));

		mp = new Politician(createPolitician("John", "Smith", -5, -5, -5));
	}

	virtual void TearDown() {
		delete ideaA;
		delete ideaB;
		delete ideaC;
		delete mp;
	}

	const Idea createIdea(const std::string name, const int socLib, const int econLib, const int envProg) {

		Characteristics::Characteristic socLiberal("socLiberal", socLib);
		Characteristics::Characteristic econLiberal("econLiberal", econLib);
		Characteristics::Characteristic enviroProgressive("enviroProgressive", envProg);
		Characteristics characs({ socLiberal, econLiberal, enviroProgressive });
		Idea idea(name, name, characs);

		return idea;
	}

	Politician createPolitician(const std::string firstName, const std::string lastName, const int socLib, const int econLib, const int envProg) {
		Characteristics::Characteristic socLiberal("socLiberal", socLib);
		Characteristics::Characteristic econLiberal("econLiberal", econLib);
		Characteristics::Characteristic enviroProgressive("enviroProgressive", envProg);
		Characteristics characs({ socLiberal, econLiberal, enviroProgressive });
		Politician mp(firstName, lastName, characs);

		return mp;
	}

	MPIsingModel* model;
	Politician* mp;
	Idea *ideaA, *ideaB, *ideaC;
};

//////////////////////////////////////////////////////////////////////////////////
//
// The tests below use the default parameters of the MP Ising model
//////////////////////////////////////////////////////////////////////////////////


TEST_F(MPIsingTest, ideaDiffusionProbabilityTest) {

	// If an idea's characteristics equal that of the politician, it
	// should be guaranteed to be adopted provided there is space
	ASSERT_EQ(1, model->ideaDiffusionProbability(mp,*ideaA, 0));

	// If an idea is as far as possible from the politician's characteristics,
	// it should be incredibly unlikely to be adopted
	EXPECT_NEAR(0, model->ideaDiffusionProbability(mp, *ideaC, 0), 0.05);

	ASSERT_TRUE(model->ideaDiffusionProbability(mp, *ideaB, 0) >
		        model->ideaDiffusionProbability(mp, *ideaC, 0));

	ASSERT_TRUE(model->ideaDiffusionProbability(mp, *ideaB, 0) <
		        model->ideaDiffusionProbability(mp, *ideaA, 0));

	// The probability of adopting an idea half as distant as the maximum
	// should be fairly small
	ASSERT_TRUE(model->ideaDiffusionProbability(mp, *ideaB, 0) < 0.1);
}

TEST_F(MPIsingTest, ideaDistanceTest) {

	Idea ideaA = createIdea("A", 5, 5, 5);
	Idea ideaB = createIdea("B", 1, 1, 1);
	Politician mp = createPolitician("John", "Smith", 1, 1, 1);

	// If an idea has the same characteristics as the mp it it optimal
	ASSERT_EQ(0, model->calculateMPIdeaDistance(&mp, ideaB));

	Idea ideaC = createIdea("C", -1, 0, 1);
	Idea ideaD = createIdea("D", 1, 0, -1);

	//Characteristics are treated with equal weight
	ASSERT_TRUE(model->calculateMPIdeaDistance(&mp, ideaC) == model->calculateMPIdeaDistance(&mp, ideaD));

	mp.addIdea(ideaA);

	// If an idea has the same characteristics as an idea held
	// by an mp it is not necessarily optimal
	ASSERT_NE(0, model->calculateMPIdeaDistance(&mp, ideaA));

	Idea ideaE = createIdea("E", 4, 4, 4);
	Idea ideaF = createIdea("F", 3, 3, 3);

	// Distance from the mp's characteristics carries more weight than the distance from any of thie ideas
	ASSERT_TRUE((model->calculateMPIdeaDistance(&mp,ideaF)) < (model->calculateMPIdeaDistance(&mp, ideaE)));
}