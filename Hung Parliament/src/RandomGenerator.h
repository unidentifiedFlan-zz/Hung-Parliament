#pragma once
#include "stdafx.h"
#include <random>
#include <chrono>

class RandomGenerator {

	static RandomGenerator *instance_;
	std::mt19937 generator_;

	RandomGenerator() : generator_(std::chrono::system_clock::now().time_since_epoch().count()) {}

public:
	static RandomGenerator* getInstance() {

		if (!instance_) {
			instance_ = new RandomGenerator();
		}

		return instance_;
	}

	double generateDouble() {

		std::uniform_real_distribution<double> distribution(0, 1);
		double randomDouble = distribution(generator_);

		return randomDouble;
	}

	unsigned int generate() {

		unsigned int randomInt = generator_();
		return randomInt;
	}
};

