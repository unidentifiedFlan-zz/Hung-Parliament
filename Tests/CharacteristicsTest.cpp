#include "pch.h"

#include "../Hung Parliament/src/Characteristics.h"

class characteristicsTest : public ::testing::Test {

protected:
	virtual void SetUp() {

		std::vector<Characteristics::Characteristic> characVecA, characVecB;

		Characteristics::Characteristic influence("influence", 5);
		Characteristics::Characteristic socLiberal("socLiberal", 10);
		Characteristics::Characteristic econLiberal("econLiberal", -4);
		characVecA.push_back(influence);
		characVecA.push_back(socLiberal);
		characVecA.push_back(econLiberal);

		influence.value = -1;
		socLiberal.value = 7;
		econLiberal.value = 2;

		characVecB.push_back(influence);
		characVecB.push_back(socLiberal);
		characVecB.push_back(econLiberal);

		characsA = new Characteristics(characVecA);
		characsB = new Characteristics(characVecB);
	}

	virtual void TearDown() {
		delete characsA;
		delete characsB;
	}

	Characteristics *characsA, *characsB;
};

TEST_F(characteristicsTest, getValueTest) {

	ASSERT_EQ(5, characsA->getValue("influence"));
	ASSERT_EQ(10, characsA->getValue("socLiberal"));
	ASSERT_EQ(-4, characsA->getValue("econLiberal"));
}

TEST_F(characteristicsTest, getListTest) {

	const std::vector<Characteristics::Characteristic> list = characsA->getList();

	std::vector<Characteristics::Characteristic>::const_iterator it = list.begin();

	//Should be in alphabetical order
	ASSERT_EQ(-4, it->value) << it->name; 
	ASSERT_EQ(5, (++it)->value) << it->name;
	ASSERT_EQ(10, (++it)->value) << it->name;
}

TEST_F(characteristicsTest, diffTest) {

	std::vector<Characteristics::Characteristic> diff = characsA->characteristicDiff(*characsB);
	std::vector<Characteristics::Characteristic>::const_iterator it = diff.begin();

	ASSERT_EQ(-6, it->value) << it->name;
	it++;
	ASSERT_EQ(6, it->value) << it->name;
	it++;
	ASSERT_EQ(3, it->value) << it->name;
}

TEST_F(characteristicsTest, distanceTest) {
	double distance = characsA->characteristicDistance(*characsB);

	ASSERT_EQ(9, distance);
}