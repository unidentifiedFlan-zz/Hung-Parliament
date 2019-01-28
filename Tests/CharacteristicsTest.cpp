#include "pch.h"

#include "../Hung Parliament/src/Characteristics.h"

class characteristicsTest : public ::testing::Test {

protected:
	virtual void SetUp() {

		std::vector<Characteristics::Characteristic> characVecA, characVecB;

		Characteristics::Characteristic influence(INFLUENCE, INFLUENCE_VALUE_A);
		Characteristics::Characteristic socLiberal(SOCLIBERAL, SOCLIBERAL_VALUE_A);
		Characteristics::Characteristic econLiberal(ECONLIBERAL, ECONLIBERAL_VALUE_A);
		characVecA.push_back(influence);
		characVecA.push_back(socLiberal);
		characVecA.push_back(econLiberal);

		influence.value = INFLUENCE_VALUE_B;
		socLiberal.value = SOCLIBERAL_VALUE_B;
		econLiberal.value = ECONLIBERAL_VALUE_B;

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
	
	int INFLUENCE_VALUE_A = 5, INFLUENCE_VALUE_B = -1,
		SOCLIBERAL_VALUE_A = 10, SOCLIBERAL_VALUE_B = 7,
		ECONLIBERAL_VALUE_A = -4, ECONLIBERAL_VALUE_B = 2;

	std::string INFLUENCE = "influence", SOCLIBERAL = "socLiberal", ECONLIBERAL = "econLiberal";

	Characteristics *characsA, *characsB;
};

TEST_F(characteristicsTest, getValueTest) {

	ASSERT_EQ(INFLUENCE_VALUE_A, characsA->getValue(INFLUENCE));
	ASSERT_EQ(SOCLIBERAL_VALUE_A, characsA->getValue(SOCLIBERAL));
	ASSERT_EQ(ECONLIBERAL_VALUE_A, characsA->getValue(ECONLIBERAL));
}

TEST_F(characteristicsTest, getListTestShouldReturnAlphabeticalOrder) {

	const std::vector<Characteristics::Characteristic> list = characsA->getList();

	std::vector<Characteristics::Characteristic>::const_iterator it = list.begin();

	//Should be in alphabetical order
	ASSERT_EQ(ECONLIBERAL_VALUE_A, it->value) << it->name; 
	ASSERT_EQ(INFLUENCE_VALUE_A, (++it)->value) << it->name;
	ASSERT_EQ(SOCLIBERAL_VALUE_A, (++it)->value) << it->name;
}

TEST_F(characteristicsTest, characteristicDiffShouldReturnInstanceValuesMinusParameterValuesTest) {

	std::vector<Characteristics::Characteristic> diff = characsA->characteristicDiff(*characsB);
	std::vector<Characteristics::Characteristic>::const_iterator it = diff.begin();



	ASSERT_EQ(ECONLIBERAL_VALUE_A - ECONLIBERAL_VALUE_B, it->value) << it->name;
	it++;
	ASSERT_EQ(INFLUENCE_VALUE_A - INFLUENCE_VALUE_B, it->value) << it->name;
	it++;
	ASSERT_EQ(SOCLIBERAL_VALUE_A - SOCLIBERAL_VALUE_B, it->value) << it->name;
}

TEST_F(characteristicsTest, distanceTest) {
	double distance = characsA->characteristicDistance(*characsB);

	double ExpValue = sqrt(pow(INFLUENCE_VALUE_A - INFLUENCE_VALUE_B, 2) + pow(ECONLIBERAL_VALUE_A - ECONLIBERAL_VALUE_B, 2)
		+ pow(SOCLIBERAL_VALUE_A - SOCLIBERAL_VALUE_B, 2));
	ASSERT_EQ(ExpValue, distance);
}