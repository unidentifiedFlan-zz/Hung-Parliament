#include "stdafx.h"
#include "politicianBuilder.h"

PoliticianBuilder::PoliticianBuilder(Parliament * parliament, std::vector<std::string> &characNames) : parliament_(parliament)
{
	personBuilder_ = new PersonBuilder(300);
	characsGen_ = new CharacteristicsGenerator(characNames);
}

Person PoliticianBuilder::generatePerson() {

	return personBuilder_->generatePerson();
}

void PoliticianBuilder::setCharacteristics() {
	characteristics_ = new Characteristics(characsGen_->generateCharacteristics());
}

Politicians PoliticianBuilder::build(const unsigned int numPoliticians) {

	Politicians newPoliticians;

	for (unsigned int i = 0; i < numPoliticians; ++i) {
		Person newPerson = generatePerson();
		setCharacteristics();
		Politician mp(newPerson, *characteristics_, parliament_);
		newPoliticians.add(mp);
	}

	return newPoliticians;
}

PoliticianBuilder::~PoliticianBuilder()
{
	delete personBuilder_;
	delete characsGen_;
	delete characteristics_;
}
