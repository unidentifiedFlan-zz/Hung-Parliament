#pragma once
#include "stdafx.h"
#include "Characteristics.h"
#include "Ideas.h"
#include "Publisher.h"
#include "Person.h"
#include "HistoryLogger.h"
#include <mutex>

class Politician : public Publisher, public Person {

	std::mutex available_;

	Characteristics characteristics_;

	Ideas ideas_;

	//Stores the opinions previously generated so they do not need to be recalculated.
	//Should be cleared whenever the polticians ideas or characteristics change
	HistoryLogger<Idea, Opinion> opinionHistory_;

	const Idea& getWeakestIdea();

public:
	static const unsigned int PERSUASION_THRESHOLD = 3;
	static const unsigned int MAXIDEAS = 3;

	Politician(std::string firstName, std::string lastName, Characteristics traits);
	Politician(Person person, Characteristics traits, Listener *Legislature);
	//Custom copy constructor required as mutex cannot be copied
	Politician(const Politician &politician);

	//Custom copy operator required as mutex cannot be copied
	Politician& operator = (const Politician &politician) {
		firstName_ = politician.firstName_;
		lastName_ = politician.lastName_;
		description_ = politician.description_;
		hello_ = politician.hello_;
		goodbye_ = politician.goodbye_;
		characteristics_ = politician.characteristics_;
		ideas_ = politician.ideas_;
		opinionHistory_ = politician.opinionHistory_;
		listeners_ = politician.listeners_;

		return *this;
	}

	const bool isAvailable();
	void setAvailable();

	const Characteristics getCharacteristics() const;

	bool addIdea(const Idea &newIdea);
	bool removeIdea(const Idea &oldIdea);
	const Ideas& getIdeas() const;
	const bool hasIdea(const Idea &Idea) const;
	const bool replaceWeakestIdea(const Idea &idea);
	const bool persuadedByIdea(const Idea &idea);

	const Opinion getOpinion(const Idea &idea);
	const Opinion generateOpinion(const Idea &idea);
	
	~Politician();
};