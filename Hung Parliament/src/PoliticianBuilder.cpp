#include "stdafx.h"
#include "politicianBuilder.h"

PoliticianBuilder::PoliticianBuilder(Parliament * parliament, std::vector<std::string> &characNames) : parliament_(parliament)
{
	personBuilder_ = new PersonBuilder(300);
	characsGen_ = new CharacteristicsGenerator(characNames);
}

Person PoliticianBuilder::genPerson() {

	return personBuilder_->genPerson();
}

void PoliticianBuilder::setCharacteristics() {
	characteristics_ = new Characteristics(characsGen_->generateCharacteristics());
}

Politician PoliticianBuilder::build() {

	Person newPerson = genPerson();
	setCharacteristics();
	Politician mp (newPerson, *characteristics_, parliament_);

	return mp;
}

PoliticianBuilder::~PoliticianBuilder()
{
	delete personBuilder_;
	delete characsGen_;
	delete characteristics_;
}
