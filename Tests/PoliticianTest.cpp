#include "pch.h"
#include "../Hung Parliament/src/Politician.h"

////////////////////////////////////////////////////////////////////////////
// Test case setup
//
////////////////////////////////////////////////////////////////////////////
class politicianTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		Characteristics::Characteristic charac(characteristicLabel, characteristicValue);
		Characteristics characs({ charac });
		newIdea = new Idea("new idea", "new idea", characs);

		firstName = "John";
		lastName = "Smith";
		mp = new Politician(firstName, lastName, characs);
		mp->addIdea(*newIdea);
	}
	virtual void TearDown() {
		delete newIdea;
		delete mp;
	}

	const Idea *newIdea;
	Politician *mp;
	std::string firstName, lastName, characteristicLabel = "liberal";
	int characteristicValue = 5;
};

TEST_F(politicianTest, hasIdeaTest) {

	Characteristics::Characteristic charac("influence", 5);
	Characteristics characs({ charac });
	Idea badIdea("bad idea", "bad idea", characs);

	ASSERT_TRUE(mp->hasIdea(*newIdea));
	ASSERT_FALSE(mp->hasIdea(badIdea));
}

TEST_F(politicianTest, removeIdeaTest) {
	mp->removeIdea(*newIdea); 

	ASSERT_FALSE(mp->hasIdea(*newIdea));
}

TEST_F(politicianTest, getListOfIdeasTest) {

	Ideas ideas = mp->getIdeas();
	Ideas::Iterator it = ideas.getFirst();

	ASSERT_EQ("new idea", it->getDescription());
}

TEST_F(politicianTest, nameTest) {

	ASSERT_EQ("John", mp->getFirstName());
	ASSERT_EQ("Smith", mp->getLastName());
}

TEST_F(politicianTest, weakestIdeaTest) {

	Characteristics::Characteristic influence("influence", 0);
	Characteristics::Characteristic socLiberal("socLiberal", 0);
	Characteristics::Characteristic econLiberal("econLiberal", 0);
	Characteristics weakCharacs({ influence, socLiberal, econLiberal });

	const Idea weakIdea("Weak idea", "Weak idea", weakCharacs);

	influence.value = -1;
	socLiberal.value = -1;
	econLiberal.value = -1;
	Characteristics weakerCharacs({ influence, socLiberal, econLiberal });

	const Idea weakerIdea("Weaker idea", "Weaker idea", weakerCharacs);

	influence.value = -5;
	socLiberal.value = -5;
	econLiberal.value = -5;
	Characteristics weakestCharacs({ influence, socLiberal, econLiberal });

	const Idea weakestIdea("Weakest idea", "Weakest idea", weakestCharacs);

	influence.value = 10;
	socLiberal.value = 10;
	econLiberal.value = 10;
	Characteristics strongCharacs({ influence, socLiberal, econLiberal });
	
	const Idea StrongIdea("Strong idea", "Strong idea", strongCharacs);
	Politician mp(firstName, lastName, strongCharacs);

	ASSERT_FALSE(mp.getIdeas().includes(weakIdea));
	mp.addIdea(weakIdea);
	ASSERT_TRUE(mp.getIdeas().includes(weakIdea));
	ASSERT_FALSE(mp.getIdeas().includes(weakerIdea));
	mp.addIdea(weakerIdea);
	ASSERT_TRUE(mp.getIdeas().includes(weakerIdea));
	ASSERT_FALSE(mp.getIdeas().includes(weakestIdea));
	mp.addIdea(weakestIdea);
	ASSERT_TRUE(mp.getIdeas().includes(weakestIdea));

	ASSERT_TRUE(mp.replaceWeakestIdea(StrongIdea));
	ASSERT_FALSE(mp.getIdeas().includes(weakestIdea));

	ASSERT_TRUE(mp.getIdeas().includes(StrongIdea));
}

TEST_F(politicianTest, persuadedByIdeaTest) {

	ASSERT_TRUE(mp->persuadedByIdea(*newIdea)) << "NewIdea";
	mp->removeIdea(*newIdea);

	//Create threshold idea
	Characteristics::Characteristic characThresh("liberal", 5 - Politician::PERSUASION_THRESHOLD);
	Characteristics characsThresh({ characThresh });
	const Idea thresholdIdea("ThreshIdea", "threshIdea", characsThresh);

	ASSERT_TRUE(mp->persuadedByIdea(thresholdIdea)) << "threshold idea";

	//Create distant idea
	Characteristics::Characteristic characDist("liberal", characteristicValue - Politician::PERSUASION_THRESHOLD - 1);
	Characteristics characsDist({ characDist });
	const Idea distantIdea("distantIdea", "distantIdea", characsDist);

	ASSERT_FALSE(mp->persuadedByIdea(distantIdea)) << "distantIdea";
}