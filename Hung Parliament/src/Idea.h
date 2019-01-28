#pragma once

#include "stdafx.h"
#include "Characteristics.h"
#include "Opinions.h"

class Idea {

	// ID is used to ensure copies still identify as the same idea. It is
	// assigned only in the constructors; the copy constructor and assignment
	// operator will copy the original's ID


	std::string name_;
	std::string description_;
	int influence_;
	Characteristics characteristics_;
	Opinions opinions_;

	const unsigned int generateID();

public:
	const unsigned int id_;
	Idea(std::string name, std::string descrip, Characteristics characs, Opinions opinions);
	Idea(std::string name, std::string descrip, Characteristics characs);

	bool operator ==(const Idea &idea) const {
		return id_ == idea.id_;
	}

	bool operator !=(const Idea &idea) const {
		return id_ != idea.id_;
	}

	bool operator <(const Idea &idea) const {
		return id_ < idea.id_;
	}

	bool operator >(const Idea &idea) const {
		return id_ > idea.id_;
	}

	const std::string getName() const;

	const std::string getDescription() const;

	const int getInfluence() const;

	const Characteristics getCharacteristics() const;

	const Opinions getOpinions() const;

	void addOpinion(Opinion opinion);

	void removeOpinion(Opinion opinion);

	~Idea();
};

