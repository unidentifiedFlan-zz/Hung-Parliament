#pragma once
#include "stdafx.h"
#include "Characteristics.h"
#include "Idea.h"
#include "Publisher.h"
#include "Person.h"
#include "HistoryLogger.h"
#include <mutex>

class Politician : public Publisher, public Person {

	std::mutex available_;

	Characteristics characteristics_;

	//The number of ideas will typically be less than 10 so a vector will suffice
	std::vector<const Idea*> ideas_;

	//Stores the opinions previously generated so they do not need to be recalculated.
	//Should be cleared whenever the polticians ideas or characteristics change
	HistoryLogger<const Idea*, const std::string> opinionHistory_;

	double ideaIdeaDistance(const Idea* theIdea);
public:

	// Persuasion threshold is the max characteristic difference from which
	// an MP will adopt an idea
	static const int PERSUASION_THRESHOLD = 3;
	static const int MAXIDEAS = 3;

	Politician(std::string firstName, std::string lastName, Characteristics traits);
	Politician(Person person, Characteristics traits, Listener *Legislature);
	//Custom copy constructor required as mutex cannot be copied
	Politician(const Politician &politician);

	bool operator = (const Politician& politician) {
		//Custum copy operator required as mutex cannot be copied
		firstName_ = politician.firstName_;
		lastName_ = politician.lastName_;
		description_ = politician.description_;
		hello_ = politician.hello_;
		goodbye_ = politician.goodbye_;
		characteristics_ = politician.characteristics_;
		ideas_ = politician.ideas_;
		opinionHistory_ = politician.opinionHistory_;
		listeners_ = politician.listeners_;
	}

	const bool isAvailable();
	void setAvailable();

	const Characteristics getCharacteristics() const;

	bool addIdea(const Idea* newIdea);
	bool removeIdea(const Idea* oldIdea);
	const std::vector<const Idea*>& getListOfIdeas() const;
	double calculateIdeaDistance(const Idea* idea);
	const Idea* replaceWeakestIdea(const Idea* idea);
	const Idea* getWeakestIdea() const;
	const bool hasIdea(const Idea *Idea) const;

	const bool persuadedByIdea(const Idea *idea);

	const std::string getOpinion(const Idea* theIdea);
	const std::string generateOpinion(const Idea* theIdea);
	
	~Politician();
};