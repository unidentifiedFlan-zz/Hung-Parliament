#include "gtest/gtest.h"
#include "../Hung Parliament/src/Idea.h"

class ideaTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		Characteristics::Characteristic charac("influence", 5);
		std::vector< Characteristics::Characteristic> characsList({ charac });
		characs = new Characteristics(characsList);
	}
	virtual void TearDown() {
		delete characs;
	}

	std::string descrip = "A new Idea";
	Characteristics *characs;
};

TEST_F(ideaTest, getDescriptionTest) {	
	Idea newIdea(descrip, descrip, *characs);
	ASSERT_EQ(descrip, newIdea.getDescription());
}

TEST_F(ideaTest, getCharacteristicsTest) {
	Idea newIdea(descrip,  descrip, *characs);
	ASSERT_EQ(5, newIdea.getCharacteristics().getValue("influence"));
}