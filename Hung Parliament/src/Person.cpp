#include "stdafx.h"
#include "Person.h"


Person::Person(std::string firstName, std::string lastName, std::string description) : 
	            firstName_(firstName), lastName_(lastName), description_(description)
{
}

const std::string Person::getFirstName() const {
	return firstName_;
}

const std::string Person::getLastName() const {
	return lastName_;
}

const std::string Person::getDescription() const {
	return description_;
}

const std::string Person::sayHello() const {
	return hello_;
}

const std::string Person::sayGoodbye() const {
	return goodbye_;
}

std::string Person::setHello(std::string newHello) {
	hello_ = newHello;
	return newHello;
}

std::string Person::setGoodbye(std::string newGoodbye) {
	goodbye_ = newGoodbye;
	return newGoodbye;
}

Person::~Person()
{
}
