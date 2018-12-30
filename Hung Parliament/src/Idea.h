#pragma once

#include "stdafx.h"
#include "Characteristics.h"
#include "Opinion.h"

class Idea {

protected:
	std::string name_;
	std::string description_;
	int influence_;
	Characteristics characteristics_;
	std::vector<Opinion> opinions_;

public:
	Idea(std::string name, std::string descrip, Characteristics characs, std::vector<Opinion> opinions);
	Idea(std::string name, std::string descrip, Characteristics characs);

	const std::string getName() const;

	const std::string getDescription() const;

	const int getInfluence() const;

	const Characteristics getCharacteristics() const;

	const std::vector<Opinion> getOpinions() const;

	void addOpinion(Opinion op);

	~Idea();
};

