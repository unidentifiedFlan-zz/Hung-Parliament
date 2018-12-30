//Characteristics.h
#pragma once

#include "stdafx.h"

class Characteristics
{
protected:
	std::unordered_map<std::string, int> _characs;

	const int generateValue() const;

public:
	struct Characteristic {
		std::string name;
		int value;
		Characteristic(const std::string n, int val) : name(n), value(val) {}
		bool operator < (const Characteristic &foreignCharac) {
			return name < foreignCharac.name;
		}
	};

	Characteristics(std::vector<Characteristic> characs);

	friend std::ostream& operator << (std::ostream& stream, const Characteristics &characs) {
		for (std::unordered_map<std::string, int>::const_iterator it = characs._characs.begin(); it != characs._characs.end(); ++it) {
			stream << it->first + ":\t" + std::to_string(it->second) + "\n";
		}
		return stream;
	}

	const int getValue(std::string charac) const;
	const std::vector<Characteristic> getList() const;
	const std::vector<Characteristic> characteristicDiff(const Characteristics& secondCharacteristicSet) const;
	const double characteristicDistance(const Characteristics secondCharacteristicSet) const;
};