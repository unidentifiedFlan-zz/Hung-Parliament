#include "pch.h"
#include "../Hung Parliament/src/Politician.h"
#include "../Hung Parliament/src/Idea.h"

class politicianTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		Characteristics::Characteristic charac("liberal", 5);
		Characteristics characs({ charac });

		newIdea = new Idea("new idea", "new idea", characs);

		firstName = "John";
		lastName = "Smith";
		mp = new Politician(firstName, lastName, characs);
		mp->addIdea(newIdea);
	}
	virtual void TearDown() {
		delete newIdea;
		delete mp;
	}

	const Idea *newIdea;
	Politician *mp;
	std::string firstName, lastName;
};


TEST_F(politicianTest, removeIdeaTest) {
	mp->removeIdea(newIdea); 

	ASSERT_EQ("new idea", newIdea->getDescription());
}

TEST_F(politicianTest, getListOfIdeasTest) {

	std::vector<const Idea*> ideas = mp->getListOfIdeas();
	std::vector<const Idea*>::const_iterator it = ideas.begin();

	ASSERT_EQ("new idea", (*it)->getDescription());
}

TEST_F(politicianTest, hasIdeaTest) {

	Characteristics::Characteristic charac("influence", 5);
	Characteristics characs({ charac });
	Idea badIdea("bad idea", "bad idea", characs);

	ASSERT_TRUE(mp->hasIdea(newIdea));
	ASSERT_FALSE(mp->hasIdea(&badIdea));
}

TEST_F(politicianTest, nameTest) {

	ASSERT_EQ("John", mp->getFirstName());
	ASSERT_EQ("Smith", mp->getLastName());
}

TEST_F(politicianTest, ideaDistanceTest) {

	Characteristics::Characteristic socLiberal("socLiberal", 5);
	Characteristics::Characteristic econLiberal("econLiberal", 5);
	Characteristics::Characteristic enviroProgressive("enviroProgressive", 5);
	Characteristics characsA({ socLiberal, econLiberal, enviroProgressive });

	Idea ideaA("ideaA", "ideaA", characsA);

	socLiberal.value = -1;
	econLiberal.value = 1;
	enviroProgressive.value = 0;
	Characteristics characsB({ socLiberal, econLiberal, enviroProgressive });

	Idea ideaB("ideaB", "ideaB", characsB);

	socLiberal.value = 6;
	econLiberal.value = 4;
	enviroProgressive.value = 4;
	Characteristics characsC({ socLiberal, econLiberal, enviroProgressive });

	Idea ideaC("ideaC", "ideaC", characsC);

	socLiberal.value = 1;
	econLiberal.value = 1;
	enviroProgressive.value = 1;
	Characteristics characsD({ socLiberal, econLiberal, enviroProgressive });

	Idea ideaD("ideaD", "ideaD", characsD);
	Politician mp("John", "Smith", characsD);

	ASSERT_EQ(0, mp.calculateIdeaDistance(&ideaD));

	mp.addIdea(&ideaB);
	mp.addIdea(&ideaC);

	//sum of idea distances + factor*mpIdea distance
	//distance((5- -1), (5-1), (5-0)) + distance((5-6),(5-4),(5-4)) + factor*distance((5-1).(5-1),(5-1))
	// = sqrt(77) + sqrt(3) + factor*sqrt(48)

	ASSERT_EQ(sqrt(77) + sqrt(3) + 2*sqrt(48), mp.calculateIdeaDistance(&ideaA));
}

TEST_F(politicianTest, weakestIdeaTest) {

	Characteristics::Characteristic influence("influence", 5);
	Characteristics::Characteristic socLiberal("socLiberal", -2);
	Characteristics::Characteristic econLiberal("econLiberal", 3);
	Characteristics weakCharacs({ influence, socLiberal, econLiberal });

	const Idea weakIdea("Weak idea", "Weak idea", weakCharacs);

	influence.value = 9;
	socLiberal.value = 10;
	econLiberal.value = -8;
	Characteristics strongCharacs({ influence, socLiberal, econLiberal });
	
	const Idea StrongIdea("Strong idea", "Strong idea", strongCharacs);
	Politician mp(firstName, lastName, strongCharacs);
	mp.addIdea(&weakIdea);
	mp.addIdea(&StrongIdea);

	ASSERT_EQ("Weak idea", mp.getWeakestIdea()->getDescription());
}