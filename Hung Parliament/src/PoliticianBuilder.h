#pragma once
#include "Parliament.h"
#include "Characteristics.h"
#include "Idea.h"
#include "PersonBuilder.h"
#include "CharacteristicsGenerator.h"
#include "politician.h"

class PoliticianBuilder
{
	Parliament *parliament_;
	PersonBuilder* personBuilder_;
	CharacteristicsGenerator* characsGen_;
	Characteristics* characteristics_;

public:
	PoliticianBuilder(Parliament *parliament, std::vector<std::string> &characteristicNames);
	Person genPerson();
	void setCharacteristics();
	Politician build();
	~PoliticianBuilder();
};

