#pragma once
class Person
{
protected:
	std::string firstName_;
	std::string lastName_;
	std::string description_;
	std::string hello_;
	std::string goodbye_;
public:
	Person(std::string firstName, std::string lastName, std::string decription);
	const std::string getFirstName() const;
	const std::string getLastName() const;
	const std::string getName() const;
	const std::string getDescription() const;
	const std::string sayHello() const;
	const std::string sayGoodbye() const;
	std::string setHello(std::string newHello);
	std::string setGoodbye(std::string newGoodbye);
	~Person();
};

