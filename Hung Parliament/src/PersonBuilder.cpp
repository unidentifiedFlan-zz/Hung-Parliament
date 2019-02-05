#include "stdafx.h"
#include "PersonBuilder.h"

PersonBuilder::PersonBuilder(int numPersons) : numPersons_(numPersons) {

	tinyxml2::XMLError error = doc.LoadFile("xml/politicians.xml");

	if (error) {
		std::cout << "Error politicians.xml not read." << std::endl;
		return;
	}

	tinyxml2::XMLElement *root = doc.RootElement();

	if (root != nullptr) {

		person = root->FirstChildElement("person");

		int n = 0;
		while (person && n < numPersons_) {

			std::string pFirstName, pLastName, pDescription, pHello, pGoodbye;

			pFirstName = parseFirstName();
			pLastName = parseLastName();
			pDescription = parseDescription();
			pHello = parseHello();
			pGoodbye = parseGoodbye();

			Person newPerson(pFirstName, pLastName, pDescription);
			newPerson.setHello(pHello);
			newPerson.setGoodbye(pGoodbye);

			persons_.push_back(newPerson);

			person = person->NextSiblingElement("person");
		}
	}
}

const std::string PersonBuilder::parseFirstName() {

	std::string firstName;
	tinyxml2::XMLElement *firstNameElem = person->FirstChildElement("firstName");
	if (firstNameElem != nullptr) {
		firstName = firstNameElem->GetText();
	}

	return firstName;
}

const std::string PersonBuilder::parseLastName() {

	std::string lastName;
	tinyxml2::XMLElement *lastNameElem = person->FirstChildElement("lastName");
	if (lastNameElem != nullptr) {
		lastName = lastNameElem->GetText();
	}

	return lastName;
}

const std::string PersonBuilder::parseDescription() {

	std::string description;
	tinyxml2::XMLElement *descriptionElem = person->FirstChildElement("description");
	if (descriptionElem != nullptr) {
		description = descriptionElem->GetText();
	}

	return description;
}

const std::string PersonBuilder::parseHello() {
	std::string hello;
	tinyxml2::XMLElement *helloElem = person->FirstChildElement("hello");
	if (helloElem != nullptr) {
		hello = helloElem->GetText();
	}

	return hello;
}

const std::string PersonBuilder::parseGoodbye() {
	std::string goodbye;
	tinyxml2::XMLElement *goodbyeElem = person->FirstChildElement("goodbye");
	if (goodbyeElem != nullptr) {
		goodbye = goodbyeElem->GetText();
	}

	return goodbye;
}

const Person PersonBuilder::generatePerson() {

	if (persons_.size() == 0) {
		return manualBuild();
	}

	if (nextGen >= persons_.size()) {
		nextGen = 0;
	}

	return persons_[nextGen++];
}

Person PersonBuilder::manualBuild() {
	Person newPerson("John", "Smith", "");
	return newPerson;
}

PersonBuilder::~PersonBuilder()
{
}
