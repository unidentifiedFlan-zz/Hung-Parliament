#include "stdafx.h"
#include "CharacteristicsGenerator.h"

namespace {

	double logisticFunction(double x) {

		double value = 1 / (1 + exp(-x));

		if (value > 1) {
			return 1;
		}
		else if (value < -1) {
			return -1;
		}

		return value;
	}
}

CharacteristicsGenerator::CharacteristicsGenerator(std::vector<std::string> &characsNames) : characs_(characsNames)
{
	int num = characs_.size();

	std::random_device rd{};
	std::mt19937 gen{ rd() };
	generator_ = gen;

	std::normal_distribution<double> distribution(0, 1.5);
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

	// Shift by -0.5 to get negative values
	double shiftedLogFunc = logisticFunction(num) - 0.5;

	// Multiply by 2 because shifted range is -0.5 to 0.5
	// and we want -1 to 1
	double value = 2*MAX_ABS_VALUE*shiftedLogFunc;
	
	value = round(value);

	return value;
}