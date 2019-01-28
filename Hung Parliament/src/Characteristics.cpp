#include "stdafx.h"
#include "Characteristics.h"


Characteristics::Characteristics(std::vector<Characteristic> traits) {

	for (std::vector<Characteristic>::iterator it = traits.begin(); it != traits.end(); ++it) {

		_characs.emplace(it->name, it->value);
	}
}

Characteristics::Characteristics() {}

void Characteristics::addCharacteristic(const Characteristic &charac) {
	_characs.emplace(charac.name, charac.value);
}

const int Characteristics::getValue(std::string charac) const{

	try{
		std::unordered_map<std::string, int>::const_iterator it = _characs.find(charac);
		
		if (it == _characs.end()) {
			throw "Error: Characteristic " + charac + " does not exist";
		}

		return it->second;
	}
	catch (std::string e) {
		std::cout << e << std::endl;
	}

	return 0;
}

const std::vector<Characteristics::Characteristic> Characteristics::getList() const {

	std::vector<Characteristic> characVec;

	for (std::unordered_map<std::string, int>::const_iterator it = _characs.begin(); it != _characs.end(); ++it) {
		Characteristic charac(it->first, it->second);
		characVec.push_back(charac);
	}

	std::sort(characVec.begin(), characVec.end());

	return characVec;
}

const std::vector<Characteristics::Characteristic> Characteristics::characteristicDiff(
																		const Characteristics& foreignCharacs) const {

	std::vector<Characteristic> foreignList = foreignCharacs.getList();

	for (std::vector<Characteristic>::iterator foreignIter = foreignList.begin(); foreignIter != foreignList.end(); ++foreignIter) {

		std::unordered_map<std::string, int>::const_iterator localIter = _characs.find(foreignIter->name);
		if (localIter == _characs.end()) {
			//If Characteristic not found, we assume local object is flexible/neutral with respect to that characteristic
			foreignIter->value = 0;
		}
		else{
			foreignIter->value = localIter->second - foreignIter->value;
		}
	}

	return foreignList;
}

const double Characteristics::characteristicDistance(const Characteristics secondCharacteristicList) const {

	double distance = 0;
	const std::vector<Characteristic> characDiff =  characteristicDiff(secondCharacteristicList);
	for (std::vector<Characteristic>::const_iterator it = characDiff.begin(); it != characDiff.end(); ++it) {
		distance += it->value*it->value;
	}

	return sqrt(distance);
}

const int Characteristics::generateValue() const {

	return 1;
}