#include "gtest/gtest.h"
#include "idea.h"

class ideaTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		characs.emplace("influence", 5);
	}
	virtual void TearDown() {

	}
	std::string descrip = "A new Idea";
	std::map<std::string, int> characs;
};

TEST_F(ideaTest, getDescriptionTest) {	
	Idea newIdea(descrip, characs);
	ASSERT_EQ(descrip, newIdea.getDescription());
}

TEST_F(ideaTest, getCharacteristicsTest) {
	Idea newIdea(descrip, characs);
	ASSERT_EQ(5, newIdea.getCharacteristics().getValue("influence"));
}