#pragma once
#include "stdafx.h"
#include "Person.h"
#include "tinyxml2.h"

class PersonBuilder
{
	bool useManualBuild_ = false;

	int numPersons_ = 0;
	unsigned int nextGen = 0;
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLElement *person;
	std::vector<Person> persons_;

	const std::string parseFirstName();
	const std::string parseLastName();
	const std::string parseDescription();
	const std::string parseHello();
	const std::string parseGoodbye();
	Person manualBuild();

public:
	PersonBuilder(int numPersons);
	const Person genPerson();
	
	~PersonBuilder();
};

