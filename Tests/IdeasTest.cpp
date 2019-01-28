#include "pch.h"
#include "../Hung Parliament/src/Ideas.h"

class ideasTest : public ::testing::Test {
protected:
	virtual void SetUp() {
		Characteristics::Characteristic charac("influence", 5);
		std::vector< Characteristics::Characteristic> characsList({ charac });
		Characteristics characs(characsList);
		newIdea = new Idea(descrip, descrip, characs);

		ideas.add(*newIdea);
	}
	virtual void TearDown() {
		delete newIdea;
	}

	Idea *newIdea;
	Ideas ideas;
	std::string descrip = "A new Idea";
};

TEST_F(ideasTest, shouldReturnTrueIfIdeasIncludesIdeaTest) {

	ASSERT_TRUE(ideas.includes(*newIdea));
}

TEST_F(ideasTest, shouldReturnTrueIfIncludesIdeaCopyTest) {

	Idea ideaCopy(*newIdea);
	ASSERT_TRUE(ideas.includes(ideaCopy));
}

TEST_F(ideasTest, shouldReturnFirstIdeaTest) {

	ASSERT_EQ(*newIdea, *ideas.getFirst());
}
