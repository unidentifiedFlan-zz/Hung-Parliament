#include "stdafx.h"
#include "CharacteristicsGenerator.h"


CharacteristicsGenerator::CharacteristicsGenerator(std::vector<std::string> &characsNames) : characs_(characsNames)
{
	int num = characs_.size();

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	generator_ = gen;

	std::normal_distribution<double> distribution(0.0, 3.0);
	distribution_ = distribution;
}

Characteristics CharacteristicsGenerator::generateCharacteristics() {

	std::vector<Characteristics::Characteristic> characVec;
	for (unsigned int i = 0; i < characs_.size(); ++i) {
		Characteristics::Characteristic charac(characs_[i], generateRandomValue());
		characVec.push_back(charac);
	}
	Characteristics characs(characVec);
	return characs;
}

double CharacteristicsGenerator::generateRandomValue() {

	double num = distribution_(generator_);

	while (std::abs(num) > 5) {
		num = distribution_(generator_);
	}

	return num;
}