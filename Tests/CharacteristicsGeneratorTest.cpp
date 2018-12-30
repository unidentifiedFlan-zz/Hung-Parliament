#include "pch.h"

#include "../Hung Parliament/src/CharacteristicsGenerator.h"


class characteristicsGeneratorTest : public ::testing::Test {

protected:
	virtual void SetUp() {

		std::vector<std::string> characNames = { "influence", "socLiberal", "econLiberal" };

		CharacteristicsGenerator characGen(characNames);

		for (int i = 0; i < 300; i++) {
			Characteristics c = characGen.generateCharacteristics();
			characList.push_back(c);
		}

	}

	virtual void TearDown() {

	}

	std::vector<Characteristics> characList;
};

TEST_F(characteristicsGeneratorTest, characsLessThan5Test) {

	for (std::vector<Characteristics>::iterator it1 = characList.begin(); it1 != characList.end(); ++it1) {
		std::vector<Characteristics::Characteristic> list = it1->getList();
		for (std::vector<Characteristics::Characteristic>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
			ASSERT_TRUE(std::abs(it2->value) <= 5);
		}
	}	
}

TEST_F(characteristicsGeneratorTest, normalDistTest) {

	double sum = 0;
	int numCharacs = characList.size()*characList[0].getList().size();

	for (std::vector<Characteristics>::iterator it1 = characList.begin(); it1 != characList.end(); ++it1) {
		std::vector<Characteristics::Characteristic> list = it1->getList();
		for (std::vector<Characteristics::Characteristic>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
			sum += it2->value;
		}
	}

	double mean = sum / (numCharacs);
	EXPECT_NEAR(0, mean, 0.5);

	for (std::vector<Characteristics>::iterator it1 = characList.begin(); it1 != characList.end(); ++it1) {
		std::vector<Characteristics::Characteristic> list = it1->getList();
		for (std::vector<Characteristics::Characteristic>::iterator it2 = list.begin(); it2 != list.end(); ++it2) {
			sum += pow(it2->value - mean,2);
		}
	}

	double stdDev = sqrt(sum / (numCharacs));
	EXPECT_NEAR(2, stdDev, 0.5);

}
