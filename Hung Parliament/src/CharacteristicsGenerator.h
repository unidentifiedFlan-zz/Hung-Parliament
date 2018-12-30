#pragma once
#include <random>
#include "Characteristics.h"

class CharacteristicsGenerator
{
	int MAX_ABS_VALUE = 5;

	std::vector<std::string> characs_;
	std::mt19937 generator_;
	std::normal_distribution<double> distribution_;

	double generateRandomValue();

public:
	CharacteristicsGenerator(std::vector<std::string> &characsNames);
	Characteristics generateCharacteristics();
};

